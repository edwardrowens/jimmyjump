#pragma once

#include<math.h>
#include<vector>
#include "Line.h"
/*
Currently used in my hit detection algorithm (which is not being used due to Box2d)
*/
namespace LineCalculationService {
	float calculateSlopeOfMovement(const Point& previous, const Point& current);
	float calculateAngleOfMovement(const Point& previous, const Point& current);
	int calculateInterceptOfMovement(const Point& point, const float& slopeOfMovement);
	Point intersectionOfTwoLines(const Line& line1, const Line& line2);
}

