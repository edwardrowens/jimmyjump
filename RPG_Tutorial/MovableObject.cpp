#include "MovableObject.h"

// Default constructor
MovableObject::MovableObject() : 
Object(),
health(100.0f), 
strength(10.0f), 
speed(5),
isStable(true), 
previousXYPosition(new int[2]),
currentMovement(Movements::NONE), 
stepCount(0){
	isMovable = true;
	previousXYPosition[0] = position.x;
	previousXYPosition[1] = position.y;
}

// Position and character constructor.
MovableObject::MovableObject(Position position, Character character) : 
Object(position, character),
health(100.0f),
strength(10.0f), 
speed(5), 
isStable(true), 
previousXYPosition(new int[2]),
currentMovement(Movements::NONE), 
stepCount(0){
	isMovable = true;
	previousXYPosition[0] = position.x;
	previousXYPosition[1] = position.y;
}

MovableObject::MovableObject(const MovableObject &movableObject): Object(movableObject),
previousXYPosition(new int[2]), currentMovement(Movements::NONE), stepCount(0){
	previousXYPosition[0] = position.x;
	previousXYPosition[1] = position.y;
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
	setY(position.y - 10);
	currentMovement = Movements::JUMP;
}

void MovableObject::moveRight(){
	setX(position.x += speed);
	if (currentMovement == Movements::LEFT || stepCount >= walkCycles['R'].size()){
		stepCount = 0;
	}
	currentMovement = Movements::RIGHT;
	std::set<string> rightWalkCycleFiles = walkCycles['R'];
	texturePath = *(walkCycles['R'].find("R" + std::to_string(stepCount)));
	++stepCount;
}

void MovableObject::moveLeft(){
	setX(position.x -= speed);
	if (currentMovement == Movements::RIGHT || stepCount >= walkCycles['L'].size()){
		stepCount = 0;
	}

	currentMovement = Movements::LEFT;
	std::set<string> rightWalkCycleFiles = walkCycles['L'];
	texturePath = *(walkCycles['L'].find("L" + std::to_string(stepCount)));
	++stepCount;
}

void MovableObject::useItem(){

}

float MovableObject::attack(){
	return strength;
}

float MovableObject::calcAngleOfMovement() const{
	float deltaY = position.y - previousXYPosition[1];
	float deltaX = previousXYPosition[0] - position.x;

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
	float deltaY = position.y - previousXYPosition[1];
	float deltaX = previousXYPosition[0] - position.x;

	if (deltaX == 0.0f){
		return 0;
	}

	return (deltaY / deltaX);
}
