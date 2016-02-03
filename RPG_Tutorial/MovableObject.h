#pragma once
#include "Object.h"
#include <math.h>
#include <string>
#include "Movements.h"
#include "CharacterInformation.h"

using std::string;
const float INIT_SPEEDY = 30.0f;
const int INIT_SPEED_X = 3;

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
	int getSpeedX() const;
	int getSpeedY() const;
	bool getIsJumping() const;
	bool getIsStable() const;
	Movements getCurrentMovement() const;
	Movements getPreviousMovement() const;
	std::vector<int> getPreviousXY() const;
	float getGravity() const;
	std::vector<float> getMotionVector() const;
	float getMotionVectorY() const;
	float getMotionVectorX() const;

	// Setters
	void setStrength(const float& newStrength);
	void setHealth(const float& newHealth);
	void setSpeedX(const int& speedX);
	void setSpeedY(const int& speedY);
	void setIsJumping(const bool& isJumping);
	void setIsStable(const bool& isColliding);
	void setCurrentMovement(const Movements& movement);
	void setPreviousMovement(const Movements& movement);
	void setPreviousXY(const int& x, const int& y);
	void setGravity(const float& gravity);
	void setMotionVectorX(const float& x);
	void setMotionVectorY(const float& y);
	void setMotionVector(const float& x, const float& y);

	// Functions
	bool jump();
	bool moveRight();
	bool moveLeft();
	void executeMovement();
	void useItem();
	float calcAngleOfMovement() const;
	float calcSlopeOfMovement() const;
	float attack();

	// Fields
	Movements currentMovement;
	Movements previousMovement;

protected:
	// Functions
	void accelerateLeftward();
	void accelerateRightward();

	// Fields
	float strength, health, gravity;
	int speedX;
	float speedY;
	std::vector<int> previousXYPosition;
	int stepCount;
	float maxXVelocity;
	float maxYVelocity;

private:
	bool isJumping, isStable;
	const float JUMP_VECTOR = 100.0f;
	int currentJumpTicks;
	std::vector<float> motionVector;

};

