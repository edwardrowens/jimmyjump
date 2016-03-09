#include "Line.h"


Line::Line()
{
}

Line::Line(Point startPoint, Point endPoint) : startPoint(startPoint), endPoint(endPoint) {
}

Line::~Line()
{
}

Point Line::getEndPoint() const {
	return endPoint;
}

Point Line::getStartPoint() const {
	return startPoint;
}

void Line::setStartPoint(const Point& startPoint) {
	this->startPoint = startPoint;
}

void Line::setEndPoint(const Point& endPoint) {
	this->endPoint = endPoint;
}

float Line::calculateLineLength() {
	return 0.0f;
}