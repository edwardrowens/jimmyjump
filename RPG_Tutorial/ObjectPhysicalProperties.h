#pragma once
#include <Box2D\Box2D.h>

enum ObjectBodies {
	NONE,
	EXAMPLE
};

struct ObjectPhysicalProperties {
	b2BodyType bodyType;
	float32 x, y, halfWidth, halfHeight, density, friction;
	ObjectBodies physicalBody;
};

ObjectPhysicalProperties& objectPhysicalProperties(const ObjectBodies& objectBody);

