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

Point& Point::operator+ (const Point& rhs) {
	this->x += rhs.getX();
	this->y += rhs.getY();

	return *this;
}

Point& Point::operator+= (const Point& rhs) {
	return this->operator+(rhs);
}

Point& Point::operator- (const Point& rhs) {
	this->x -= rhs.getX();
	this->y -= rhs.getY();

	return *this;
}

Point& Point::operator-= (const Point& rhs) {
	return this->operator-(rhs);
}

float Point::crossProduct(const Point& rhs) {
	return this->x * rhs.getY() - this->y * rhs.getX();
}

float Point::dotProduct(const Point& rhs) {
	return this->x * rhs.getX() + this->y * rhs.getY();
}