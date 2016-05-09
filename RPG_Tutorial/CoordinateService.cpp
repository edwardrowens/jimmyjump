#include "CoordinateService.h"

b2Vec2 CoordinateService::screenToWorld(const int &x, const int &y) {
	return b2Vec2((x - WorldConstants::X_ORIGIN) * WorldConstants::METER_TO_PIXEL, (WorldConstants::Y_ORIGIN - y) * WorldConstants::METER_TO_PIXEL);
}


b2Vec2 CoordinateService::worldToScreen(const float &x, const float &y) {
	return b2Vec2(WorldConstants::X_ORIGIN + (x / WorldConstants::METER_TO_PIXEL), WorldConstants::Y_ORIGIN - (y / WorldConstants::METER_TO_PIXEL));
}