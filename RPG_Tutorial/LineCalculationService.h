#pragma once

#include<math.h>
#include<vector>

namespace LineCalculationService {
	float calculateSlopeOfMovement(const int& currentX, const int& currentY, const int& previousX, const int& previousY);
	float calculateAngleOfMovement(const int& currentX, const int& currentY, const int& previousX, const int& previousY);
	int calculateInterceptOfMovement(const int& currentX, const int& currentY, const float& slopeOfMovement);
	std::vector<int> intersectionOfTwoLines(const std::vector<int>& start1, const std::vector<int>& end1, const std::vector<int>& start2, const std::vector<int>& end2);
}

