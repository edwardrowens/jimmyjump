#pragma once

#include "Point.h"

class Line
{
public:
	Line();
	Line(Point startPoint, Point endPoint);
	~Line();

	Line& operator+ (const Line& rhs);
	Line& operator+= (const Line& rhs);

	Point getEndPoint() const;
	Point getStartPoint() const;

	void setStartPoint(const Point& startPoint);
	void setEndPoint(const Point& endPoint);

private:
	Point startPoint, endPoint;
	float length;

	float calculateLineLength();
};

