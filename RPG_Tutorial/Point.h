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

	Point& operator+ (const Point& rhs);
	Point& operator+= (const Point& rhs);
	Point& operator- (const Point& rhs);
	Point& operator-= (const Point& rhs);

	float crossProduct(const Point& rhs);
	float dotProduct(const Point& rhs);
private:
	int x, y;
};

