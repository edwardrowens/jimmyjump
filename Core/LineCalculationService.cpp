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
		Point p = line1.getStartPoint();
		Point q = line2.getStartPoint();
		Point r = line1.getEndPoint() - p;
		Point s = line2.getEndPoint() - q;

		float denominator = r.crossProduct(s);
		float uNumerator = (q - p).crossProduct(r);

		// collinear points
		if (denominator == 0 && uNumerator == 0) {
			float t0 = (q - p).dotProduct(r) / (r.dotProduct(r));
			float t1 = t0 + s.dotProduct(r) / r.dotProduct(r);
		}

		float t = ((q - p).crossProduct(s)) / denominator;
		float u = uNumerator / denominator;

		if (denominator != 0.0f && t >= 0.0f && t <= 1.0f && u >= 0.0f && u <= 1.0f)
			return (p + (r * t));
		
		return Point(-1, -1);
	}
}
