#include "CollisionDetector.h"


CollisionDetector::CollisionDetector()
{
}


CollisionDetector::~CollisionDetector()
{
}

void CollisionDetector::detectStaticCollisions(MovableObject* object, const std::vector<Object*> &levelObjects){
	SDL_Rect intersection;

	int iteration, intercept, depthOfPenetration = 0;
	iteration = intercept = depthOfPenetration;
	float slope, angle = 0.0f;

	for (int i = 0; i < levelObjects.size(); ++i){
		if (!levelObjects[i]->getIsMovable() && levelObjects[i]->getCharacter() != Character::BACKGROUND){
			if (SDL_IntersectRect(levelObjects[i]->getHitbox(), object->getHitbox(), &intersection)){
				// get line parameters
				slope = object->calcSlopeOfMovement();
				angle = object->calcAngleOfMovement();
				intercept = object->getY() - (object->getX() * (-1 * slope));

				// find the smaller rectangle
				SDL_Rect smallerRect = SDL_Rect();
				SDL_Rect levelObjectRect = *levelObjects[i]->getHitbox();
				SDL_Rect movableObjectRect = *object->getHitbox();
				if (levelObjectRect.h == intersection.h || levelObjectRect.w == intersection.w)
					smallerRect = levelObjectRect;
				else
					smallerRect = movableObjectRect;

				// is the intersection a corner intersection
				bool cornerResolution = intersection.w != smallerRect.w && intersection.h != smallerRect.h;

				// intersected either from the left or right
				if (smallerRect.y == intersection.y && (smallerRect.x < intersection.x || smallerRect.x == intersection.x) && smallerRect.w != intersection.w && !cornerResolution){
					// intersecting from right
					if (angle > 90 && angle < 270)
						object->setX(object->getX() + intersection.w);
					else
						object->setX(object->getX() - intersection.w);
				}
				// intersected from up or down
				else if (intersection.x == smallerRect.x && smallerRect.y <= intersection.y && !cornerResolution){
					if (angle >= 0 && angle < 180)
						object->setY(object->getY() + intersection.h);
					else
						object->setY(object->getY() - intersection.h);
				}
				else if (cornerResolution){
					// Did the character land on the platform?
					if (object->getPreviousXY()[1] + movableObjectRect.h <= levelObjectRect.y)
						object->setY(object->getY() - intersection.h);
					else if ((smallerRect.x <= intersection.x && smallerRect.y == intersection.y) && angle < 180 && angle > 0)
						object->setY(object->getY() + intersection.h);
					else{
						// Q1 or Q4?
						if ((angle < 90 && angle >= 0) || (angle > 270 && angle < 360)){
							object->setX(object->getX() - intersection.w);
						}
						// Q2 or Q3?
						else {
							object->setX(object->getX() + intersection.w);
						}
					}
				}
				else
					PrintErrors(generateResolutionErrorMessage(*object, *levelObjects[i], intersection));

				// reiterate through the loop to ensure there are no other resolutions required
				i = -1;

				// set the motion vector to 0 because we are assuming that the collision has been resolved. however, this is not
				// a good way to do this since the collision doesnt necessarily have to be with the stability of the feet.
				object->setMotionVectorY(0.0f);
			}
		}
	}
}

void CollisionDetector::detectDynamicCollisions(MovableObject* object, const std::vector<Object*> &levelObjects){
	for (auto i : levelObjects){
		if (i->getIsMovable() && i->getIsRenderable()){
			SDL_Rect intersection;
			if (i != object && SDL_IntersectRect(i->getHitbox(), object->getHitbox(), &intersection)){
				MovableObject* objectA = (MovableObject*)object;
				MovableObject* objectB = (MovableObject*)i;

				SDL_Rect objectAHitbox = *(object->getHitbox());
				SDL_Rect objectBHitbox = *(i->getHitbox());

				float angleA = objectA->calcAngleOfMovement();
				float angleB = objectB->calcAngleOfMovement();

				resolveObjectAggression(objectA, objectB, intersection);
			}
		}
	}
}

std::string CollisionDetector::generateResolutionErrorMessage(const Object &a, const Object &b, const SDL_Rect &i){
	return "No resolution found for:\n\n" + a.getTexturePath() + ":\n\t(" + std::to_string(a.getX()) + ", " + std::to_string(a.getY())
		+ ") W = " + std::to_string(a.getWidth()) + ", H = " + std::to_string(a.getHeight()) + "\n\n" + b.getTexturePath() + ":\n\t(" + std::to_string(b.getX()) + ", " + std::to_string(b.getY())
		+ ") W = " + std::to_string(b.getWidth()) + ", H = " + std::to_string(b.getHeight()) + "\n\n" + "Intersection:\n\t(" + std::to_string(i.x) + ", " + std::to_string(i.y)
		+ ") W = " + std::to_string(i.w) + ", H = " + std::to_string(i.h) + "\n";
}

/*
Calculate the distance of separation between the two rectangles

@param smallerRect The smaller of the two rectangles in the intersection
@param i The intersection rectangle
*/
int CollisionDetector::calcDepthOfPenetration(const SDL_Rect &smallerRect, const SDL_Rect &i){
	if ((i.x == smallerRect.x && i.y == smallerRect.y) || smallerRect.x < i.x && smallerRect.y == i.y){
		return i.w;
	}
	else if ((i.x == smallerRect.x && i.y != smallerRect.y) || (i.x != smallerRect.x && i.y == smallerRect.y)){
		return i.h;
	}
	else{
		return round(sqrt(i.w ^ 2 + i.h ^ 2));
	}
}

bool CollisionDetector::calcStability(SDL_Rect object, SDL_Rect intersection, float angle){
	if (angle < 360 && angle > 180)
		return true;
	else
		return false;
}

void CollisionDetector::resolveObjectAggression(MovableObject* objectA, MovableObject* objectB, const SDL_Rect &intersection) {
	resolveObjectAggressionInXDirection(objectA, objectB, intersection);
	if (!objectA->getIsStable() && !objectB->getIsStable())
		resolveObjectAggressionInYDirection(objectA, objectB, intersection);
}

void CollisionDetector::resolveObjectAggressionInXDirection(MovableObject* objectA, MovableObject* objectB, const SDL_Rect& intersection){
	float absoluteXVelocity = std::abs(objectA->getMotionVectorX()) - std::abs(objectB->getMotionVectorX());
	if (absoluteXVelocity < .001){
		if (objectB->calcAngleOfMovement() < 90.0f || objectB->calcAngleOfMovement() > 270.0f){
			objectB->setX(objectB->getX() - (intersection.w / 2));
			objectA->setX(objectA->getX() + (intersection.w / 2));
		}
		else{
			objectB->setX(objectB->getX() + (intersection.w / 2));
			objectA->setX(objectA->getX() - (intersection.w / 2));
		}
	}
	else if (absoluteXVelocity > 0.0f) {
		if (objectB->getPreviousXY()[0] != objectB->getX()){
			if (objectA->calcAngleOfMovement() < 90.0f || objectA->calcAngleOfMovement() > 270.0f)
				objectB->setX(objectB->getX() + intersection.w);
			else
				objectB->setX(objectB->getX() - intersection.w);
		}
	}
	else {
		if (objectA->getPreviousXY()[0] != objectA->getX()){
			if (objectB->calcAngleOfMovement() < 90.0f || objectB->calcAngleOfMovement() > 270.0f)
				objectA->setX(objectA->getX() + intersection.w);
			else
				objectA->setX(objectA->getX() - intersection.w);
		}
	}
}

void CollisionDetector::resolveObjectAggressionInYDirection(MovableObject* objectA, MovableObject* objectB, const SDL_Rect &intersection) {
	float absoluteYVelocity = std::abs(objectA->getMotionVectorY()) - std::abs(objectB->getMotionVectorY());
	float angleA = objectA->calcAngleOfMovement();
	float angleB = objectB->calcAngleOfMovement();

	if (!objectA->getIsStable() && !objectB->getIsStable()) {

	}
	else if (!objectA->getIsStable()) {

	}
	else {

	}

	if (absoluteYVelocity < .001){
		if (angleB < 180.0f && angleB > 0.0f){
			objectB->setY(objectB->getY() - (intersection.h / 2));
			objectA->setY(objectA->getY() + (intersection.h / 2));
		}
		else{
			objectB->setY(objectB->getY() + (intersection.h / 2));
			objectA->setY(objectA->getY() - (intersection.h / 2));
		}
	}
	else if (absoluteYVelocity > 0.0f) {
		if (!objectB->getIsStable()){
			if (angleA < 180.0f && angleA > 0.0f)
				objectB->setY(objectB->getY() - intersection.h);
			else
				objectB->setY(objectB->getY() + intersection.h);
		}
	}
	else {
		if (!objectA->getIsStable()){
			if (angleB < 180.0f && angleB > 0.0f)
				objectA->setY(objectA->getY() - intersection.h);
			else
				objectA->setY(objectA->getY() + intersection.h);
		}
	}
}