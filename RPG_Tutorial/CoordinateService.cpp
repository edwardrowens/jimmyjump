#include "CoordinateService.h"

b2Vec2 CoordinateService::screenToWorld(const int &x, const int &y) {
	return b2Vec2((x - WorldConstants::X_ORIGIN) / WorldConstants::PIXELS_PER_METER, (WorldConstants::Y_ORIGIN - y) / WorldConstants::PIXELS_PER_METER);
}


b2Vec2 CoordinateService::worldToScreen(const float32 &x, const float32 &y) {
	return b2Vec2((WorldConstants::X_ORIGIN + (x * WorldConstants::PIXELS_PER_METER)), WorldConstants::Y_ORIGIN - (y * WorldConstants::PIXELS_PER_METER));
}


/*
Calculates the delta between the 2 vectors (meters) then converts them into a delta in pixels.
*/
b2Vec2 CoordinateService::displacementFromWorldToScreen(const b2Vec2 &previousPosition, const b2Vec2 &currentPosition) {
	b2Vec2 displacement = currentPosition - previousPosition;
	displacement *= WorldConstants::PIXELS_PER_METER;
	return displacement;
}