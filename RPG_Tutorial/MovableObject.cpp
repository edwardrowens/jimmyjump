#include "MovableObject.h"


//initiating stats to arbitrary values
MovableObject::MovableObject() : health(100.0f), strength(10.0f), speed(5),
isStable(true), previousXYPosition(new int[2]),
currentMovement(Movements::none){
	isMovable = true;
	previousXYPosition[0] = x;
	previousXYPosition[1] = y;
}

MovableObject::MovableObject(int x, int y, int width, int height) : Object(x, y, width, height), health(100.0f),
strength(10.0f), speed(5), isStable(true), previousXYPosition(new int[2]),
currentMovement(Movements::none){
	isMovable = true;
	previousXYPosition[0] = x;
	previousXYPosition[1] = y;
}

MovableObject::MovableObject(const MovableObject &movableObject): Object(movableObject),
previousXYPosition(new int[2]), currentMovement(Movements::none){
	previousXYPosition[0] = x;
	previousXYPosition[1] = y;
}

MovableObject::~MovableObject(){
	delete previousXYPosition;
}

MovableObject& MovableObject::operator=(const MovableObject &moveableObject){
	Object::operator=(moveableObject);
	
	return *this;
}



float MovableObject::getStrength() const{
	return strength;
}

float MovableObject::getHealth() const{
	return health;
}

int MovableObject::getSpeed() const{
	return speed;
}


bool MovableObject::getIsStable() const{
	return isStable;
}

Movements MovableObject::getCurrentMovement() const{
	return currentMovement;
}

Movements MovableObject::getPreviousMovement() const{
	return previousMovement;
}

int* MovableObject::getPreviousXY() const{
	return previousXYPosition;
}

void MovableObject::setStrength(const float& strength){
	this->strength = strength;
}

void MovableObject::setHealth(const float& health){
	this->health = health;
}

void MovableObject::setSpeed(const int& speed){
	this->speed = speed;
}


void MovableObject::setIsStable(const bool& isStable){
	this->isStable = isStable;
}

void MovableObject::setCurrentMovement(const Movements& movement){
	currentMovement = movement;
}

void MovableObject::setPreviousMovement(const Movements& movement){
	previousMovement = movement;
}

void MovableObject::setPreviousXY(const int& x, const int& y){
	previousXYPosition[0] = x;
	previousXYPosition[1] = y;
}


void MovableObject::jump(){
	setY(y - 10);
	currentMovement = Movements::JUMP;
}

void MovableObject::moveRight(){
	setX(x += speed);
	currentMovement = Movements::RIGHT;
}

void MovableObject::moveLeft(){
	setX(x -= speed);
	currentMovement = Movements::LEFT;
}

void MovableObject::useItem(){

}

float MovableObject::attack(){
	return strength;
}

float MovableObject::calcAngleOfMovement() const{
	float deltaY = y - previousXYPosition[1];
	float deltaX = previousXYPosition[0] - x;

	// no movement
	if (deltaX == 0 && deltaY == 0)
		return 0.0f;

	// vertical movement
	if (deltaX == 0){
		if (deltaY > 0){
			return 270.0f;
		}
		else{
			return 90.0f;
		}
	}

	// horizontal movement
	if (deltaY == 0){
		if (deltaX > 0)
			return 0.0f;
		else
			return 180.0f;
	}
	float angle = atan(deltaY / deltaX) * 180 / M_PI;

	// Q1
	if (deltaX < 0 && deltaY < 0){
		return angle;
	}
	// Q2
	else if (deltaX > 0 && deltaY < 0){
		return angle * -1 + 90;
	}
	// Q3
	else if (deltaX > 0 && deltaY > 0){
		return angle += 180;
	}
	// Q4
	else {
		return angle * -1 + 270;
	}
}

float MovableObject::calcSlopeOfMovement() const{
	float deltaY = y - previousXYPosition[1];
	float deltaX = previousXYPosition[0] - x;

	if (deltaX == 0.0f){
		return 0;
	}

	return (deltaY / deltaX);
}
