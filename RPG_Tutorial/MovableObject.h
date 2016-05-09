#pragma once
#include "Object.h"
#include <math.h>
#include <string>
#include <random>
#include "Movements.h"
#include "CharacterInformation.h"

using std::string;

const float32 MAX_X_VELOCITY = 5.0f;
const float32 MAX_Y_VELOCITY = 5.0f;
const float32 X_VELOCITY_STEP = 2.5f;
const float32 Y_VELOCITY_STEP = 2.5f;


class MovableObject : public Object {
public:
	// Constructors and destructor.
	MovableObject(b2Body* objectBody, Character character);
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
	std::vector<Movements> getCurrentMovements() const;
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
	void setPreviousXY(const int& x, const int& y);
	void setGravity(const float& gravity);
	void setMotionVectorX(const float& x);
	void setMotionVectorY(const float& y);
	void setMotionVector(const float& x, const float& y);
	void setMaxVelocityX(const float& xVelocity);
	void setSpeedX(const float& speedX);

	// Functions
	void addMovement(const Movements& movement);
	void executeMovement();
	void useItem();
	float attack();

	// Fields
	std::vector<Movements> currentMovements;

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
	// Fields
	bool isJumping, isStable, isPatrolling;
	char patrolDirection;
	const float JUMP_VECTOR = 50.0f;
	int currentJumpTicks;
	std::vector<float> motionVector;
	int patrolDistance = 100;
	int patrolDistanceTraveled;
	int stuckCount = 0;

	// Functions
	void switchPatrolDirection();
	bool jump();
	void patrol();
	virtual void moveRight();
	virtual void moveLeft();
};

