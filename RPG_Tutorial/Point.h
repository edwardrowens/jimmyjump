#pragma once
class Point
{
public:
	Point();
	Point(const int& x, const int& y);
	~Point();

	int getX() const;
	int getY() const;

	void setX(const int& x);
	void setY(const int& y);

	const Point operator+ (const Point& rhs) const;
	const Point operator- (const Point& rhs) const;
	const Point operator* (const float& rhs) const;
	Point& operator+= (const Point& rhs);
	Point& operator-= (const Point& rhs);
	Point& operator*= (const float& rhs);

	float crossProduct(const Point& rhs) const;
	float dotProduct(const Point& rhs) const;
private:
	int x, y;
};

