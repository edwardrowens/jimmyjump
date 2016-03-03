#pragma once

#include<math.h>
#include<vector>
#include "Line.h"

namespace LineCalculationService {
	float calculateSlopeOfMovement(const Point& previous, const Point& current);
	float calculateAngleOfMovement(const Point& previous, const Point& current);
	int calculateInterceptOfMovement(const Point& point, const float& slopeOfMovement);
	Point intersectionOfTwoLines(const Line& line1, const Line& line2);
}

