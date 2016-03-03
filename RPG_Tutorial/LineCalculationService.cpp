#include "LineCalculationService.h"

namespace LineCalculationService{
	float calculateSlopeOfMovement(const Point& previous, const Point& current) {
		float deltaY = current.getY() - previous.getY();
		float deltaX = previous.getX() - current.getX();

		if (deltaX == 0.0f)
			return 0;

		return (deltaY / deltaX);
	}

	float calculateAngleOfMovement(const Point& previous, const Point& current) {
		float deltaY = current.getY() - previous.getY();
		float deltaX = previous.getX() - current.getX();

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
		float angle = atan(deltaY / deltaX) * 180 / 3.14159;

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

	int calculateInterceptOfMovement(const Point& point, const float& slopeOfMovement) {
		return point.getY() - (point.getX() * (-1 * slopeOfMovement));
	}

	Point intersectionOfTwoLines(const Line& line1, const Line& line2) {
		float lineOneSlope = calculateSlopeOfMovement(line1.getStartPoint(), line1.getEndPoint());
		float lineTwoSlope = calculateSlopeOfMovement(line2.getStartPoint(), line2.getEndPoint());

		float lineOneIntercept = calculateInterceptOfMovement(line1.getEndPoint(), lineOneSlope);
		float lineTwoIntercept = calculateInterceptOfMovement(line2.getEndPoint(), lineTwoSlope);

		float interceptSubtraction = lineTwoIntercept - lineOneIntercept;
		float slopeSubtraction = lineOneSlope - lineTwoSlope;

		float x = interceptSubtraction / slopeSubtraction;
		float y = (lineOneSlope * x) + lineOneIntercept;
		
		return Point(x, y);
	}
}
