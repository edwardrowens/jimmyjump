#pragma once
#include "ObjectManager.h"
#include <Box2D\Box2D.h>

class World
{
public:
	World();
	~World();

private:
	b2World boxWorld;
	ObjectManager objectManager;
};

namespace WorldConstants {
	const b2Vec2 DEFAULT_GRAVITY(0.0f, -10.0f);
}