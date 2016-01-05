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
		if (levelObjects[i]->getIsPlatform()){
			if (SDL_IntersectRect(levelObjects[i]->getHitbox(), object->getHitbox(), &intersection)){
				Movements m = object->getCurrentMovement();
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
			}
		}
	}
}

void CollisionDetector::detectDynamicCollisions(MovableObject* object, const std::vector<Object*> &levelObjects){

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
