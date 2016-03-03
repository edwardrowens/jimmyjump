#include "Line.h"


Line::Line()
{
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

float calculateLineLength() {

}

Line& Line::operator+ (const Line& rhs) {
}

Line& Line::operator+= (const Line& rhs) {

}