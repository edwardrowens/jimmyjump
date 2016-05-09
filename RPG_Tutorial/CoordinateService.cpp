#include "CoordinateService.h"

b2Vec2 CoordinateService::screenToWorld(const int &x, const int &y) {
	return b2Vec2((x - WorldConstants::X_ORIGIN) / WorldConstants::PIXELS_PER_METER,
				  (-y + WorldConstants::Y_ORIGIN) / WorldConstants::PIXELS_PER_METER);
}

//http://box2d.org/forum/viewtopic.php?t=8198
b2Vec2 CoordinateService::worldToScreen(const float &x, const float &y) {
	return b2Vec2((x + (WorldConstants::X_ORIGIN / WorldConstants::PIXELS_PER_METER)) * WorldConstants::PIXELS_PER_METER,
				  (-y + (WorldConstants::Y_ORIGIN / WorldConstants::PIXELS_PER_METER)) * WorldConstants::PIXELS_PER_METER);
}