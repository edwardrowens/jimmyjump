#pragma once
#include <Box2D\Box2D.h>
#include "ObjectPhysicalProperties.h"

namespace Box2dMapper {
	b2FixtureDef mapToFixture(const ObjectPhysicalProperties &props);
	b2BodyDef mapToBody(const ObjectPhysicalProperties &props);
	b2PolygonShape mapToShape(const ObjectPhysicalProperties &props);
}

