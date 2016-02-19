#pragma once
#include "Object.h"
#include "Errors.h"
#include <vector>
#include "MovableObject.h"
#include "Movements.h"

class CollisionDetector
{
public:
	CollisionDetector();
	~CollisionDetector();

public:
	static void detectStaticCollisions(MovableObject* object, const std::vector<Object*> &levelObjects);
	static void detectDynamicCollisions(MovableObject* object, const std::vector<Object*> &levelObjects);

private:
	static int calcDepthOfPenetration(const SDL_Rect &smallerRect, const SDL_Rect &intersection);
	static std::string generateResolutionErrorMessage(const Object &a, const Object &b, const SDL_Rect &i);
	static bool calcStability(SDL_Rect object, SDL_Rect intersection, float angle);
	static void resolveObjectAggression(MovableObject* objectA, MovableObject* objectB, const SDL_Rect &intersection);
	static void resolveObjectAggressionInXDirection(MovableObject* objectA, MovableObject* objectB, const SDL_Rect &intersection);
	static void resolveObjectAggressionInYDirection(MovableObject* objectA, MovableObject* objectB, const SDL_Rect &intersection);
};

