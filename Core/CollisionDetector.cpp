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

	for (int i = 0; i < levelObjects.size(); ++i){
		if (!levelObjects[i]->getIsMovable() && levelObjects[i]->getCharacter() != Character::BACKGROUND && object != levelObjects[i]){
			if (SDL_IntersectRect(levelObjects[i]->getHitbox(), object->getHitbox(), &intersection)){
				resolveStaticCollision(object, levelObjects[i], intersection);

				// reiterate through the loop to ensure there are no other resolutions required
				i = -1;
			}
		}
	}
}

void CollisionDetector::resolveStaticCollision(MovableObject* object, Object* staticObject, const SDL_Rect& intersection) {
	// get line parameters
	float slope = LineCalculationService::calculateSlopeOfMovement(Point(object->getPreviousXY()[0], object->getPreviousXY()[1]), Point(object->getX(), object->getY()));
	float angle = LineCalculationService::calculateAngleOfMovement(Point(object->getPreviousXY()[0], object->getPreviousXY()[1]), Point(object->getX(), object->getY()));
	int intercept = LineCalculationService::calculateInterceptOfMovement(Point(object->getX(), object->getY()), slope);

	// find the smaller rectangle
	SDL_Rect smallerRect = SDL_Rect();
	SDL_Rect levelObjectRect = *staticObject->getHitbox();
	SDL_Rect movableObjectRect = *object->getHitbox();
	if (levelObjectRect.h == intersection.h || levelObjectRect.w == intersection.w)
		smallerRect = levelObjectRect;
	else
		smallerRect = movableObjectRect;

	// is the intersection a corner intersection
	bool cornerResolution = intersection.w != smallerRect.w && intersection.h != smallerRect.h;

	if ((object->getPreviousXY()[1] + object->getHeight()) <= staticObject->getY() && isMovingDownward(angle)) {
		object->setY(object->getY() - intersection.h);
	}
	else if (angle > 45.0f && angle <= 135.0f)
		object->setY(object->getY() + intersection.h);
	else if (angle > 135.0f && angle <= 215.0f)
		object->setX(object->getX() + intersection.w);
	else if (angle > 215.0f && angle <= 315.0f)
		object->setY(object->getY() - intersection.h);
	else if (angle > 315.0f || angle <= 45.0f)
		object->setX(object->getX() - intersection.w);
	//// intersected either from the left or right
	//if (smallerRect.y == intersection.y && (smallerRect.x < intersection.x || smallerRect.x == intersection.x) && smallerRect.w != intersection.w && !cornerResolution){
	//	// intersecting from right
	//	if (angle > 90 && angle < 270)
	//		object->setX(object->getX() + intersection.w);
	//	else
	//		object->setX(object->getX() - intersection.w);
	//}
	//// intersected from up or down
	//else if (intersection.x == smallerRect.x && smallerRect.y <= intersection.y && !cornerResolution){
	//	if (angle >= 0 && angle < 180)
	//		object->setY(object->getY() + intersection.h);
	//	else
	//		object->setY(object->getY() - intersection.h);
	//}
	//else if (cornerResolution){
	//	// Did the character land on the platform?
	//	if (object->getPreviousXY()[1] + movableObjectRect.h <= levelObjectRect.y){
	//		object->setY(object->getY() - intersection.h);
	//		object->setMotionVectorY(0.0f);
	//	}
	//	else if ((smallerRect.x <= intersection.x && smallerRect.y == intersection.y) && angle < 180 && angle > 0)
	//		object->setY(object->getY() + intersection.h);
	//	else{
	//		// Q1 or Q4?
	//		if ((angle < 90 && angle >= 0) || (angle > 270 && angle < 360)){
	//			object->setX(object->getX() - intersection.w);
	//		}
	//		// Q2 or Q3?
	//		else {
	//			object->setX(object->getX() + intersection.w);
	//		}
	//	}
	//}
	else
		PrintErrors(generateResolutionErrorMessage(*object, *staticObject, intersection));

	// set the motion vector to 0 because we are assuming that the collision has been resolved. however, this is not
	// a good way to do this since the collision doesnt necessarily have to be with the stability of the feet.
}

void CollisionDetector::detectDynamicCollisions(MovableObject* object, const std::vector<Object*> &levelObjects){
	for (auto i : levelObjects){
		if (i->getIsMovable() && i->getIsRenderable()){
			SDL_Rect intersection;
			if (i != object && SDL_IntersectRect(i->getHitbox(), object->getHitbox(), &intersection)){
				MovableObject* objectA = (MovableObject*)object;
				MovableObject* objectB = (MovableObject*)i;

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

void CollisionDetector::resolveObjectAggression(MovableObject* objectA, MovableObject* objectB, const SDL_Rect& intersection) {
	if (objectA->getIsStable() && objectB->getIsStable() && objectA->getY() != objectB->getY()) {
		// if both are stable but there was a dynamic collision and one Y is greater than another, this must 
		// mean that one object fell two frames ago. So who is it? once we find out who, we will treat the 
		// object who fell two frames ago to be the one that is moving.
		if (objectA->getY() < objectB->getY())
			resolveStaticCollision(objectA, objectB, intersection);
		else
			resolveStaticCollision(objectB, objectA, intersection);
	}

	else if (!objectA->getIsStable() || !objectB->getIsStable())
		resolveObjectAggressionInYDirection(objectA, objectB, intersection);
	else
		resolveObjectAggressionInXDirection(objectA, objectB, intersection);
}

void CollisionDetector::resolveObjectAggressionInXDirection(MovableObject* objectA, MovableObject* objectB, const SDL_Rect& intersection){
	float absoluteXVelocity = std::abs(objectA->getMotionVectorX()) - std::abs(objectB->getMotionVectorX());
	float angleA = LineCalculationService::calculateAngleOfMovement(Point(objectA->getPreviousXY()[0], objectA->getPreviousXY()[1]), Point(objectA->getX(), objectA->getY()));
	float angleB = LineCalculationService::calculateAngleOfMovement(Point(objectB->getPreviousXY()[0], objectB->getPreviousXY()[1]), Point(objectB->getX(), objectB->getY()));

	if (std::abs(absoluteXVelocity) < .001){
		if (angleB < 90.0f || angleB > 270.0f){
			objectB->setX(objectB->getX() - (intersection.w / 2));
			objectA->setX(objectA->getX() + (intersection.w / 2));

			objectA->setMotionVectorX(0.0f);
			objectB->setMotionVectorX(0.0f);
		}
		else{
			objectB->setX(objectB->getX() + (intersection.w / 2));
			objectA->setX(objectA->getX() - (intersection.w / 2));

			objectA->setMotionVectorX(0.0f);
			objectB->setMotionVectorX(0.0f);
		}
	}

	// Who's the aggressor?
	else if (absoluteXVelocity > 0.0f)
		resolveGreaterXVelocityCollision(objectA, objectB, intersection);
	else
		resolveGreaterXVelocityCollision(objectB, objectA, intersection);
}

void CollisionDetector::resolveGreaterXVelocityCollision(MovableObject* greaterVelocityObject, MovableObject* lowerVelocityObject, const SDL_Rect& intersection) {
	// if the object is not moving
	if (greaterVelocityObject->getPreviousXY()[0] == greaterVelocityObject->getX()){
		greaterVelocityObject->setMotionVectorX(0.0f);
		lowerVelocityObject->setMotionVectorX(0.0f);
		return;
	}

	float greaterVelocityObjectAngle = LineCalculationService::calculateAngleOfMovement(Point(greaterVelocityObject->getPreviousXY()[0], greaterVelocityObject->getPreviousXY()[1]), Point(greaterVelocityObject->getX(), greaterVelocityObject->getY()));
	float greaterVelocityObjectXVelocity = greaterVelocityObject->getMotionVectorX();

	// The lower velocity object is not changing positions but has is reported as having velocity meaning something else is
	// pushing it but it's stuck.
	if (lowerVelocityObject->getPreviousXY()[0] == lowerVelocityObject->getX() && lowerVelocityObject->getMotionVectorX() != 0.0f){
		if (greaterVelocityObjectAngle < 90.0f || greaterVelocityObjectAngle > 270.0f){
			greaterVelocityObject->setX(greaterVelocityObject->getX() + intersection.w / 2);
			lowerVelocityObject->setX(lowerVelocityObject->getX() + intersection.w / 2);
		}
		else {
			greaterVelocityObject->setX(greaterVelocityObject->getX() - intersection.w / 2);
			lowerVelocityObject->setX(lowerVelocityObject->getX() - intersection.w / 2);
		}
	}
	else if (lowerVelocityObject->getMotionVectorX() != 0.0f) {
		if (greaterVelocityObjectXVelocity > 0)
			lowerVelocityObject->setMotionVectorX(greaterVelocityObjectXVelocity - std::abs(lowerVelocityObject->getMotionVectorX()));
		else
			lowerVelocityObject->setMotionVectorX(greaterVelocityObjectXVelocity + std::abs(lowerVelocityObject->getMotionVectorX()));

		greaterVelocityObject->setMotionVectorX(lowerVelocityObject->getMotionVectorX());
	}
	else{
		greaterVelocityObject->setMotionVectorX(0.0f);
		lowerVelocityObject->setMotionVectorX(greaterVelocityObjectXVelocity);
		if (greaterVelocityObjectAngle < 90.0f || greaterVelocityObjectAngle > 270.0f)
			greaterVelocityObject->setX(greaterVelocityObject->getX() - intersection.w);
		else
			greaterVelocityObject->setX(greaterVelocityObject->getX() - intersection.w);
	}
	if (greaterVelocityObjectAngle < 90.0f || greaterVelocityObjectAngle > 270.0f)
		lowerVelocityObject->setX(lowerVelocityObject->getX() + intersection.w);
	else
		lowerVelocityObject->setX(lowerVelocityObject->getX() - intersection.w);
}

void CollisionDetector::resolveObjectAggressionInYDirection(MovableObject* objectA, MovableObject* objectB, const SDL_Rect &intersection) {
	float angleA = LineCalculationService::calculateAngleOfMovement(Point(objectA->getPreviousXY()[0], objectA->getPreviousXY()[1]), Point(objectA->getX(), objectA->getY()));
	float angleB = LineCalculationService::calculateAngleOfMovement(Point(objectB->getPreviousXY()[0], objectB->getPreviousXY()[1]), Point(objectB->getX(), objectB->getY()));

	// Both guys are in the air
	if (!objectA->getIsStable() && !objectB->getIsStable()) {
		float absoluteYVelocity = std::abs(objectA->getMotionVectorY()) - std::abs(objectB->getMotionVectorY());

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
		else {
			if (!objectB->getIsStable()){
				if (angleA < 180.0f && angleA > 0.0f)
					objectB->setY(objectB->getY() - intersection.h);
				else
					objectB->setY(objectB->getY() + intersection.h);
			}
		}
	}
	// A is in the air
	else if (!objectA->getIsStable())
		resolveStaticCollision(objectA, objectB, intersection);
	// B is in the air
	else
		resolveStaticCollision(objectB, objectA, intersection);
}

bool CollisionDetector::isMovingDownward(const float& angle) {
	return angle > 180.0f && angle < 360.0f;
}