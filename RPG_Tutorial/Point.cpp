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

const Point Point::operator+ (const Point& rhs) const {
	return Point(*this) += rhs;
}

Point& Point::operator+= (const Point& rhs) {
	x += rhs.getX();
	y += rhs.getY();

	return *this;
}

const Point Point::operator- (const Point& rhs) const {
	return Point(*this) -= rhs;
}

Point& Point::operator-= (const Point& rhs) {
	x -= rhs.getX();
	y -= rhs.getY();

	return *this;
}

// SCALAR MULTIPLICATION
const Point Point::operator* (const float& rhs) const {
	return Point(*this) *= rhs;
}

Point& Point::operator*= (const float& rhs) {
	x *= rhs;
	y *= rhs;

	return *this;
}

float Point::crossProduct(const Point& rhs) const {
	return this->x * rhs.getY() - this->y * rhs.getX();
}

float Point::dotProduct(const Point& rhs) const {
	return this->x * rhs.getX() + this->y * rhs.getY();
}