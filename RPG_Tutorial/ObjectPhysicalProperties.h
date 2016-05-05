#ifndef _OBJECTPHYSICALPROPERTIES_H
#define _OBJECTPHYSICALPROPERTIES_H
#include <Box2D\Box2D.h>

namespace ObjectBodies {
	enum ObjectBodies {
		NONE,
		EXAMPLE
	};

}


namespace ObjectPhysicalProperties {
	struct ObjectPhysicalProperties {
		b2BodyType bodyType;
		float32 x, y, halfWidth, halfHeight, density, friction;
		ObjectBodies::ObjectBodies physicalBody;
	};
}


namespace ObjectPhysicalPropertiesService {
	ObjectPhysicalProperties::ObjectPhysicalProperties objectPhysicalProperties(const ObjectBodies::ObjectBodies &objectBody);
}
#endif