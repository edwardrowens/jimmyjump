#include "ObjectPhysicalPropertiesService.h"

ObjectPhysicalProperties::ObjectPhysicalProperties ObjectPhysicalPropertiesService::objectPhysicalProperties(const ObjectBodies::ObjectBodies &objectBody) {
	ObjectPhysicalProperties::ObjectPhysicalProperties props;
	switch (objectBody) {
	case ObjectBodies::NONE:
		props.physicalBody = ObjectBodies::NONE;
	case ObjectBodies::EXAMPLE:
		props.bodyType = b2_dynamicBody;
		props.density = 1.0f;
		props.x = 200.0f;
		props.y = 100.0f;
		props.halfHeight = 1.0f;
		props.halfWidth = 1.0f;
		props.physicalBody = ObjectBodies::EXAMPLE;
		break;
	}

	return props;
}