#include "LineCalculationService.h"

namespace LineCalculationService{
	float calculateSlopeOfMovement(const int& currentX, const int& currentY, const int& previousX, const int& previousY) {
		float deltaY = currentY - previousY;
		float deltaX = previousX - currentX;

		if (deltaX == 0.0f)
			return 0;

		return (deltaY / deltaX);
	}

	float calculateAngleOfMovement(const int& currentX, const int& currentY, const int& previousX, const int& previousY) {
		float deltaY = currentY - previousY;
		float deltaX = previousX - currentX;

		// no movement
		if (deltaX == 0 && deltaY == 0)
			return 0.0f;

		// vertical movement
		if (deltaX == 0){
			if (deltaY > 0){
				return 270.0f;
			}
			else{
				return 90.0f;
			}
		}

		// horizontal movement
		if (deltaY == 0){
			if (deltaX < 0)
				return 0.0f;
			else
				return 180.0f;
		}
		float angle = atan(deltaY / deltaX) * 180 / M_PI;

		// Q1
		if (deltaX < 0 && deltaY < 0){
			return angle;
		}
		// Q2
		else if (deltaX > 0 && deltaY < 0){
			return angle * -1 + 90;
		}
		// Q3
		else if (deltaX > 0 && deltaY > 0){
			return angle += 180;
		}
		// Q4
		else {
			return angle * -1 + 270;
		}
	}

	int calculateInterceptOfMovement(const int& currentX, const int& currentY, const float& slopeOfMovement) {
		return currentY - (currentX * (-1 * slopeOfMovement));
	}

	std::vector<int> intersectionOfTwoLines(const std::vector<int>& start1, const std::vector<int>& end1, const std::vector<int>& start2, const std::vector<int>& end2) {
		std::vector<int> s = std::vector<int>();
		std::vector<int> r = std::vector<int>();

		s.push_back(start1[0] - end1[0]);
		s.push_back(start1[1] - end1[1]);

		r.push_back(start2[0] - end2[0]);
		r.push_back(start2[1] - end2[1]);
	}
}
