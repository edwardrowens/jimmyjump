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

	const float HITBOX_MODIFIER = .9;

	enum class Movements{
		right, left, none, jump, down
	};

	float getStrength() const;
	float getHealth() const;
	int getSpeed() const;
	bool getIsJumping() const;
	bool getIsStable() const;
	SDL_Rect* getHitbox() const;
	Movements getCurrentMovement() const;
	Movements getPreviousMovement() const;
	int* getPreviousXY() const;

	void setStrength(float newStrength);
	void setHealth(float newHealth);
	void setSpeed(int newSpeed);
	void setIsJumping(bool isJumping);
	void setIsStable(bool isStable);
	virtual void setWidth(int width);
	virtual void setHeight(int height);
	virtual void setX(int x);
	virtual void setY(int y);
	void setCurrentMovement(Movements movements);
	void setPreviousMovement(Movements movements);
	void setPreviousXY(int x, int y);


	void jump();
	void moveRight();
	void moveLeft();
	void useItem();
	float calcAngleOfMovement() const;
	float attack();

	Movements _currentMovement;
	Movements _previousMovement;

protected:
	float _strength, _health;
	int _speed;
	int* _previousXYPosition;
	//is the object's y position greater than then floor but should not be decremented
	bool _isStable;
	SDL_Rect* _hitbox;
};

