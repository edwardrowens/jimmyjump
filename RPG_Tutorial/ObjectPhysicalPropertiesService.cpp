#include "ObjectPhysicalPropertiesService.h"

ObjectPhysicalProperties::ObjectPhysicalProperties ObjectPhysicalPropertiesService::objectPhysicalProperties(const ObjectBodies::ObjectBodies &objectBody) {
	ObjectPhysicalProperties::ObjectPhysicalProperties props;

	props.physicalBody = objectBody;

	switch (objectBody) {
	case ObjectBodies::ObjectBodies::NONE: {
		props.bodyType = b2_staticBody;
		b2Vec2 convertedXAndY = CoordinateService::screenToWorld(0, 0);
		props.x = convertedXAndY.x;
		props.y = convertedXAndY.y;
		props.h = 0.0f;
		props.w = 0.0f;
		props.density = 0.0f;
		props.friction = 0.0f;
		break;
	}
	case ObjectBodies::ObjectBodies::EXAMPLE: {
		props.bodyType = b2_dynamicBody;
		b2Vec2 convertedXAndY = CoordinateService::screenToWorld(100, 200);
		props.x = convertedXAndY.x;
		props.y = convertedXAndY.y;
		props.h = 20.0f * WorldConstants::METER_TO_PIXEL;
		props.w = 20.0f * WorldConstants::METER_TO_PIXEL;
		props.density = 1.0f;
		props.friction = 0.3f;
		break;
	}
	case ObjectBodies::ObjectBodies::PLATFORM: {
		props.bodyType = b2_staticBody;
		b2Vec2 convertedXAndY = CoordinateService::screenToWorld(100, 500);
		props.x = convertedXAndY.x;
		props.y = convertedXAndY.y;
		props.h = 50.0f * WorldConstants::METER_TO_PIXEL;
		props.w = 50.0f * WorldConstants::METER_TO_PIXEL;
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

	b2Vec2 convertedXAndY = CoordinateService::screenToWorld(position.x, position.y);
	props.x = convertedXAndY.x;
	props.y = convertedXAndY.y;
	props.h = position.h / 2 * WorldConstants::METER_TO_PIXEL;
	props.w = position.w / 2 * WorldConstants::METER_TO_PIXEL;

	switch (objectBody) {
	case ObjectBodies::ObjectBodies::NONE:
		props.bodyType = b2_staticBody;
		break;
	case ObjectBodies::ObjectBodies::EXAMPLE:
		props.bodyType = b2_dynamicBody;
		props.density = 1.0f;
		break;
	case ObjectBodies::ObjectBodies::PLATFORM:
		props.bodyType = b2_staticBody;
		break;
	}

	return props;
}