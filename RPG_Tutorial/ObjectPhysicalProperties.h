#ifndef _OBJECTPHYSICALPROPERTIES_H
#define _OBJECTPHYSICALPROPERTIES_H
#include <Box2D\Box2D.h>
#include "ObjectBodies.h"

namespace ObjectPhysicalProperties {
	struct ObjectPhysicalProperties {
		b2BodyType bodyType;
		float32 x, y, w, h, density, friction;
		ObjectBodies physicalBody;
	};
}
#endif