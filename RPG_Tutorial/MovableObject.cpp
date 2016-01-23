#include "MovableObject.h"

// Default constructor
MovableObject::MovableObject() :
Object(),
health(100.0f),
strength(10.0f),
speed(5),
isStable(true),
currentMovement(Movements::NONE),
stepCount(0),
currentJumpTicks(1){
	isMovable = true;
	previousXYPosition.push_back(position.x);
	previousXYPosition.push_back(position.y);
}

// Position and character constructor.
MovableObject::MovableObject(Position position, Character character) :
Object(position, character),
health(100.0f),
strength(10.0f),
speed(5),
isStable(true),
currentMovement(Movements::NONE),
stepCount(0),
currentJumpTicks(1){
	isMovable = true;
	previousXYPosition.push_back(position.x);
	previousXYPosition.push_back(position.y);
}

MovableObject::MovableObject(const MovableObject &movableObject) : Object(movableObject),
currentMovement(Movements::NONE), stepCount(0){
	previousXYPosition.push_back(position.x);
	previousXYPosition.push_back(position.y);
}

MovableObject::~MovableObject(){
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

std::vector<int> MovableObject::getPreviousXY() const{
	return previousXYPosition;
}

float MovableObject::getGravity() const{
	return gravity;
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

void MovableObject::setGravity(const float& gravity){
	this->gravity = gravity;
}

void MovableObject::jump(){
	if ((previousXYPosition[1] != position.y && currentJumpTicks > 1) || (previousXYPosition[1] == position.y && currentJumpTicks == 1)){
		if ((JUMP_VECTOR - (currentJumpTicks*gravity)) > 0){
			currentMovement = Movements::JUMP;
			setY(position.y - (JUMP_VECTOR - (currentJumpTicks*gravity)));
			isStable = previousXYPosition[1] == position.y;
			++currentJumpTicks;
		}
		else{
			currentJumpTicks = 1;
			currentMovement = Movements::NONE;
			isStable = previousXYPosition[1] == position.y;
		}
	}
	else{
		currentJumpTicks = 1;
	}
}

string MovableObject::moveRight(){
	isStable = previousXYPosition[1] == position.y;
	setX(position.x += speed);
	if (currentMovement == Movements::LEFT || stepCount >= walkCycles['R'].size()){
		stepCount = 0;
	}

	// POTENTIAL PROBLEM: If I use another type of file for textures, I would have to make a more general solution rather than
	// hard-coding this string.
	currentMovement = Movements::RIGHT;
	texturePath = texturePath.substr(0, utility.getFileLocFromPath(texturePath));
	texturePath = texturePath + "R" + std::to_string(stepCount) + ".png";
	++stepCount;

	return texturePath;
}

string MovableObject::moveLeft(){
	isStable = previousXYPosition[1] == position.y;
	setX(position.x -= speed);
	if (currentMovement == Movements::RIGHT || stepCount >= walkCycles['L'].size()){
		stepCount = 0;
	}

	// POTENTIAL PROBLEM: If I use another type of file for textures, I would have to make a more general solution rather than
	// hard-coding this string.
	currentMovement = Movements::LEFT;
	texturePath = texturePath.substr(0, utility.getFileLocFromPath(texturePath));
	texturePath = texturePath + "L" + std::to_string(stepCount) + ".png";
	++stepCount;

	return texturePath;
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
		if (deltaX < 0)
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
