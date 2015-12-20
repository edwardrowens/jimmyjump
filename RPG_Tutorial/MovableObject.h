#pragma once
#include "Object.h"
#include <math.h>
#include <string>
#include "Movements.h"

class MovableObject : public Object
{
public:
	MovableObject();
	MovableObject(Position position);

	~MovableObject();
	MovableObject(const MovableObject &moveableObject);
	MovableObject& operator=(const MovableObject &moveableObject);

	float getStrength() const;
	float getHealth() const;
	int getSpeed() const;
	bool getIsJumping() const;
	bool getIsStable() const;
	Movements getCurrentMovement() const;
	Movements getPreviousMovement() const;
	int* getPreviousXY() const;

	void setStrength(const float& newStrength);
	void setHealth(const float& newHealth);
	void setSpeed(const int& newSpeed);
	void setIsJumping(const bool& isJumping);
	void setIsStable(const bool& isStable);
	void setCurrentMovement(const Movements& movement);
	void setPreviousMovement(const Movements& movement);
	void setPreviousXY(const int& x, const int& y);


	void jump();
	void moveRight();
	void moveLeft();
	void useItem();
	float calcAngleOfMovement() const;
	float calcSlopeOfMovement() const;
	float attack();

	Movements currentMovement;
	Movements previousMovement;

protected:
	float strength, health;
	int speed;
	// 0 = x, 1 = y
	int* previousXYPosition;
	//is the object's y position greater than then floor but should not be decremented
	bool isStable;

private:
	int stepCount;
};

