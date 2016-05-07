#include "ObjectPhysicalPropertiesService.h"

ObjectPhysicalProperties::ObjectPhysicalProperties ObjectPhysicalPropertiesService::objectPhysicalProperties(const ObjectBodies::ObjectBodies &objectBody) {
	ObjectPhysicalProperties::ObjectPhysicalProperties props;

	props.physicalBody = objectBody;

	switch (objectBody) {
	case ObjectBodies::ObjectBodies::NONE:
		props.bodyType = b2_staticBody;
		props.x = 0.0f;
		props.y = 0.0f;
		props.halfHeight = 0.0f;
		props.halfWidth = 0.0f;
		props.density = 0.0f;
		props.friction = 0.0f;
		break;
	case ObjectBodies::ObjectBodies::EXAMPLE:
		props.bodyType = b2_dynamicBody;
		props.density = 1.0f;
		props.x = 100.0f;
		props.y = 200.0f;
		props.halfHeight = 25.0f;
		props.halfWidth = 25.0f;
		props.density = 1.0f;
		props.friction = 0.3f;
		break;
	}

	return props;
}

ObjectPhysicalProperties::ObjectPhysicalProperties ObjectPhysicalPropertiesService::objectPhysicalProperties(const ObjectBodies::ObjectBodies &objectBody, const Position &position) {
	ObjectPhysicalProperties::ObjectPhysicalProperties props;

	props.physicalBody = objectBody;
	props.x = position.x;
	props.y = position.y;
	props.halfHeight = position.h / 2.0f;
	props.halfWidth = position.w / 2.0f;

	switch (objectBody) {
	case ObjectBodies::ObjectBodies::NONE:
		props.bodyType = b2_staticBody;
		break;
	case ObjectBodies::ObjectBodies::EXAMPLE:
		props.bodyType = b2_dynamicBody;
		props.density = 1.0f;
		break;
	}

	return props;
}