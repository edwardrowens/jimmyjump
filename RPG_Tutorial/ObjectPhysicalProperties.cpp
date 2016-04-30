#include "ObjectPhysicalProperties.h"

ObjectPhysicalProperties& objectPhysicalProperties(const ObjectBodies& objectBody) {
	ObjectPhysicalProperties props;
	switch (objectBody) {
	case NONE:
		props.physicalBody = NONE;
	case EXAMPLE:
		ObjectPhysicalProperties props;
		props.bodyType = b2_dynamicBody;
		props.density = 1.0f;
		props.x = 200.0f;
		props.y = 100.0f;
		props.halfHeight = 1.0f;
		props.halfWidth = 1.0f;
		props.physicalBody = EXAMPLE;
		break;
	}

	return props;
}
