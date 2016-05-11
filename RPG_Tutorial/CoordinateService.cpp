#include "CoordinateService.h"

b2Vec2 CoordinateService::screenToWorld(const int &x, const int &y) {
	return b2Vec2((x - WorldConstants::X_ORIGIN) / WorldConstants::PIXELS_PER_METER, (WorldConstants::Y_ORIGIN - y) / WorldConstants::PIXELS_PER_METER);
}

/*
Calculates the delta between the 2 vectors (represented in meters) then converts them into a delta in screen coordinates.
*/
b2Vec2 CoordinateService::dispalcementFromWorldToScreen(const b2Vec2 &previousPosition, const b2Vec2 &currentPosition) {
	b2Vec2 displacement = currentPosition - previousPosition;
	displacement *= WorldConstants::PIXELS_PER_METER;
	return displacement;
}