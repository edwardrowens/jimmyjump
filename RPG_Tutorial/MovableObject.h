#pragma once
#include "Object.h"
#include <math.h>
#include <string>

class MovableObject : public Object
{
public:
	MovableObject();
	MovableObject(int x, int y, int width, int height);

	~MovableObject();
	MovableObject(const MovableObject &moveableObject);
	MovableObject& operator=(const MovableObject &moveableObject);

	enum class Movements{
		right, left, none, jump, down
	};

	float getStrength() const;
	float getHealth() const;
	int getSpeed() const;
	bool getIsJumping() const;
	bool getIsStable() const;
	Movements getCurrentMovement() const;
	Movements getPreviousMovement() const;
	int* getPreviousXY() const;

	void setStrength(float newStrength);
	void setHealth(float newHealth);
	void setSpeed(int newSpeed);
	void setIsJumping(bool isJumping);
	void setIsStable(bool isStable);
	void setCurrentMovement(Movements movements);
	void setPreviousMovement(Movements movements);
	void setPreviousXY(int x, int y);


	void jump();
	void moveRight();
	void moveLeft();
	void useItem();
	float calcAngleOfMovement() const;
	float calcSlopeOfMovement() const;
	float attack();

	Movements _currentMovement;
	Movements _previousMovement;

protected:
	float _strength, _health;
	int _speed;
	// 0 = x, 1 = y
	int* _previousXYPosition;
	//is the object's y position greater than then floor but should not be decremented
	bool _isStable;
};

