#pragma once

#include "Point.h"
/*
Essentially a container which holds 2 'points' which are just 2 dimensional vectors storing
and X and Y position.
*/
class Line
{
public:
	Line();
	Line(Point startPoint, Point endPoint);
	~Line();

	Point getEndPoint() const;
	Point getStartPoint() const;

	void setStartPoint(const Point& startPoint);
	void setEndPoint(const Point& endPoint);

private:
	Point startPoint, endPoint;
	float length;

	float calculateLineLength();
};

