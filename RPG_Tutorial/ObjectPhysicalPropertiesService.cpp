#include "ObjectPhysicalPropertiesService.h"

ObjectPhysicalProperties::ObjectPhysicalProperties ObjectPhysicalPropertiesService::objectPhysicalProperties(const ObjectBodies::ObjectBodies &objectBody) {
	ObjectPhysicalProperties::ObjectPhysicalProperties props;

	props.physicalBody = objectBody;

	switch (objectBody) {
	case ObjectBodies::ObjectBodies::NONE: {
		props.bodyType = b2_staticBody;
		b2Vec2 convertedCoords = CoordinateService::screenToWorld(0, 0);
		props.x = convertedCoords.x;
		props.y = convertedCoords.y;
		props.h = 0.0f;
		props.w = 0.0f;
		props.density = 0.0f;
		props.friction = 0.0f;
		break;
	}
	case ObjectBodies::ObjectBodies::EXAMPLE: {
		props.bodyType = b2_dynamicBody;
		b2Vec2 convertedCoords = CoordinateService::screenToWorld(100, 200);
		props.x = convertedCoords.x;
		props.y = convertedCoords.y;
		props.h = 1.5f;
		props.w = 1.5f;
		props.density = 3.0f;
		props.friction = 0.3f;
		break;
	}
	case ObjectBodies::ObjectBodies::PLATFORM: {
		props.bodyType = b2_staticBody;
		b2Vec2 convertedCoords = CoordinateService::screenToWorld(WorldConstants::X_ORIGIN, 500);
		props.x = convertedCoords.x;
		props.y = convertedCoords.y;
		props.h = 3.0f;
		props.w = 40.0f;
		props.density = 1.0f;
		props.friction = 0.3f;
		break;
	}
	}

	return props;
}

ObjectPhysicalProperties::ObjectPhysicalProperties ObjectPhysicalPropertiesService::objectPhysicalProperties(const ObjectBodies::ObjectBodies &objectBody, const Position &position) {
	ObjectPhysicalProperties::ObjectPhysicalProperties props;

	props.physicalBody = objectBody;
	b2Vec2 convertedCoords = CoordinateService::screenToWorld(position.x, position.y);

	props.x = convertedCoords.x;
	props.y = convertedCoords.y;
	props.h = (float) position.h / WorldConstants::PIXELS_PER_METER;
	props.w = (float) position.w / WorldConstants::PIXELS_PER_METER;

	props.friction = 0.3f;
	props.density = 1.0f;
	switch (objectBody) {
	case ObjectBodies::ObjectBodies::NONE:
		props.bodyType = b2_staticBody;
		props.friction = 0.0f;
		props.density = 0.0f;
		break;
	case ObjectBodies::ObjectBodies::EXAMPLE:
		props.bodyType = b2_dynamicBody;
		break;
	case ObjectBodies::ObjectBodies::PLATFORM:
		props.bodyType = b2_staticBody;
		break;
	}

	return props;
}