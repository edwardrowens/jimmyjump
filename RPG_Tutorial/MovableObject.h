#pragma once
#include "Object.h"
#include <math.h>
#include <string>
#include "Movements.h"
#include "CharacterInformation.h"

class MovableObject : public Object
{
public:
	// Constructors and destructor.
	MovableObject();
	MovableObject(Position position, Character character);
	~MovableObject();
	MovableObject(const MovableObject &moveableObject);

	// Operator overloads.
	MovableObject& operator=(const MovableObject &moveableObject);

	// Getters
	float getStrength() const;
	float getHealth() const;
	int getSpeed() const;
	bool getIsJumping() const;
	bool getIsStable() const;
	Movements getCurrentMovement() const;
	Movements getPreviousMovement() const;
	int* getPreviousXY() const;

	// Setters
	void setStrength(const float& newStrength);
	void setHealth(const float& newHealth);
	void setSpeed(const int& newSpeed);
	void setIsJumping(const bool& isJumping);
	void setIsStable(const bool& isStable);
	void setCurrentMovement(const Movements& movement);
	void setPreviousMovement(const Movements& movement);
	void setPreviousXY(const int& x, const int& y);

	// Funcitons
	void jump();
	string moveRight();
	string moveLeft();
	void useItem();
	float calcAngleOfMovement() const;
	float calcSlopeOfMovement() const;
	float attack();

	// Fields
	Movements currentMovement;
	Movements previousMovement;

protected:
	float strength, health;
	int speed;
	int* previousXYPosition;
	//is the object's y position greater than then floor but should not be decremented
	bool isStable;

private:
	int stepCount;
};

