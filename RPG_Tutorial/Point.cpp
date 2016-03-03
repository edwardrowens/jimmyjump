#include "Point.h"


Point::Point(): x(0), y(0) {}

Point::Point(const int& x, const int& y) : x(x), y(y) {}

Point::~Point()
{
}

int Point::getX() const {
	return x;
}
int Point::getY() const {
	return y;
}

void Point::setX(const int& x) {
	this->x - x;
}
void Point::setY(const int& y) {
	this->y = y;
}