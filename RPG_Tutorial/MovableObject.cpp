#include "MovableObject.h"

// Default constructor
MovableObject::MovableObject() :
Object(),
health(100.0f),
strength(10.0f),
speedX(INIT_SPEED_X),
speedY(INIT_SPEED_Y),
isStable(true),
stepCount(0),
currentJumpTicks(1),
motionVector({ 0, 0 }),
maxXVelocity(INIT_MAX_VELOCITY_X),
maxYVelocity(INIT_MAX_VELOCITY_Y),
patrolDirection('R'){
	isMovable = true;
	previousXYPosition.push_back(position.x);
	previousXYPosition.push_back(position.y);
}

// Position and character constructor.
MovableObject::MovableObject(Position position, Character character) :
Object(position, character),
health(100.0f),
strength(10.0f),
speedX(INIT_SPEED_X),
speedY(INIT_SPEED_Y),
isStable(true),
stepCount(0),
currentJumpTicks(1),
motionVector({ 0, 0 }),
maxXVelocity(INIT_MAX_VELOCITY_X),
maxYVelocity(INIT_MAX_VELOCITY_Y),
patrolDirection('R'){
	isMovable = true;
	previousXYPosition.push_back(position.x);
	previousXYPosition.push_back(position.y);
}

MovableObject::MovableObject(const MovableObject &movableObject) :
Object(movableObject),
stepCount(0),
motionVector({ 0, 0 }),
isStable(true),
health(100.0f),
strength(10.0f),
speedX(INIT_SPEED_X),
speedY(INIT_SPEED_Y),
currentJumpTicks(1),
maxXVelocity(INIT_MAX_VELOCITY_X),
maxYVelocity(INIT_MAX_VELOCITY_Y),
patrolDirection('R'){
	previousXYPosition.push_back(position.x);
	previousXYPosition.push_back(position.y);
}

MovableObject::~MovableObject(){
}

// PROBLEM: does not include fields unique to MovableObject's
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

int MovableObject::getSpeedX() const{
	return speedX;
}

int MovableObject::getSpeedY() const{
	return speedY;
}

bool MovableObject::getIsStable() const{
	return isStable;
}

std::vector<Movements> MovableObject::getCurrentMovements() const{
	return currentMovements;
}

std::vector<int> MovableObject::getPreviousXY() const{
	return previousXYPosition;
}

float MovableObject::getGravity() const{
	return gravity;
}

std::vector<float> MovableObject::getMotionVector() const{
	return motionVector;
}

float MovableObject::getMotionVectorX() const{
	return motionVector[0];
}

float MovableObject::getMotionVectorY() const{
	return motionVector[1];
}

void MovableObject::setStrength(const float& strength){
	this->strength = strength;
}

void MovableObject::setHealth(const float& health){
	this->health = health;
}

void MovableObject::setSpeedX(const int& speedX){
	this->speedX = speedX;
}

void MovableObject::setSpeedY(const int& speedY){
	this->speedY = speedY;
}

void MovableObject::setIsStable(const bool& isStable){
	this->isStable = isStable;
	if (isStable)
		currentJumpTicks = 1;
}

void MovableObject::setPreviousXY(const int& x, const int& y){
	previousXYPosition[0] = x;
	previousXYPosition[1] = y;
}

void MovableObject::setGravity(const float& gravity){
	this->gravity = gravity;
}

void MovableObject::setMotionVectorX(const float& x){
	motionVector[0] = x;
}

void MovableObject::setMotionVectorY(const float& y){
	motionVector[1] = y;
}

void MovableObject::setMotionVector(const float& x, const float& y){
	motionVector[0] = x;
	motionVector[1] = y;
}

void MovableObject::setMaxVelocityX(const float& xVelocity) {
	maxXVelocity = xVelocity;
}

void MovableObject::setSpeedX(const float& speedX) {
	this->speedX = speedX;
}

bool MovableObject::jump(){
	if ((!isStable && getMotionVectorY() < 0) || isStable){
		setMotionVectorY(getMotionVectorY() - (speedY / currentJumpTicks));
		setY(position.y + getMotionVectorY());
		if (!isStable && getMotionVectorY() < 0)
			setX(position.x + getMotionVectorX());
		++currentJumpTicks;
		return true;
	}
	currentJumpTicks = 1;
	return false;
}

void MovableObject::moveRight(){
	accelerateRightward();

	if (stepCount >= walkCycles['R'].size()){
		stepCount = 0;
	}

	// POTENTIAL PROBLEM: If I use another type of file for textures, I would have to make a more general solution rather than
	// hard-coding this string.
	// POTENTIAL PROBLEM: If I use another type of file for textures, I would have to make a more general solution rather than
	// hard-coding this string.
	int fileLocInPath = utility.getFileLocFromPath(texturePath);
	char firstCharInFileName = texturePath.substr(fileLocInPath, texturePath.size())[0];

	// This checks if they have a directionality in their image files. If they don't, then we don't want to see their texturePath to
	// an invalid file.
	if (firstCharInFileName == 'R' || firstCharInFileName == 'L'){
		texturePath = texturePath.substr(0, fileLocInPath);
		texturePath = texturePath + "R" + std::to_string(stepCount) + ".png";
	}

	++stepCount;
}

void MovableObject::moveLeft(){
	accelerateLeftward();

	if (stepCount >= walkCycles['L'].size()){
		stepCount = 0;
	}

	// POTENTIAL PROBLEM: If I use another type of file for textures, I would have to make a more general solution rather than
	// hard-coding this string.
	int fileLocInPath = utility.getFileLocFromPath(texturePath);
	char firstCharInFileName = texturePath.substr(fileLocInPath, texturePath.size())[0];

	// This checks if they have a directionality in their image files. If they don't, then we don't want to see their texturePath to
	// an invalid file.
	if (firstCharInFileName == 'L' || firstCharInFileName == 'R'){
		texturePath = texturePath.substr(0, fileLocInPath);
		texturePath = texturePath + "L" + std::to_string(stepCount) + ".png";
	}

	++stepCount;
}

void MovableObject::patrol(){

	switch (patrolDirection){
	case 'L':
		moveLeft();
		break;
	case 'R':
		moveRight();
		break;
	}

	int distanceTraveledInOneFrame = std::abs(position.x - previousXYPosition[0]);
	patrolDistanceTraveled += distanceTraveledInOneFrame;
	if (distanceTraveledInOneFrame == 0){
		++stuckCount;
	}

	// If you've exceeded the patrol distance limit or did not move in the last frame (meaning you're stuck).
	// then switch direction.
	if (patrolDistanceTraveled >= patrolDistance || stuckCount > 3){
		patrolDistanceTraveled = 0;
		stuckCount = 0;
		switchPatrolDirection();
	}
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

void MovableObject::accelerateLeftward(){
	if (getMotionVectorX() > (-1 * maxXVelocity)){
		setMotionVectorX(getMotionVectorX() - speedX);
		setX(position.x + getMotionVectorX());
	}
	else {
		setMotionVectorX(-1 * maxXVelocity);
		setX(position.x - maxXVelocity);
	}
}

void MovableObject::accelerateRightward(){
	if (getMotionVectorX() < maxXVelocity){
		setMotionVectorX(getMotionVectorX() + speedX);
		setX(position.x + getMotionVectorX());
	}
	else {
		setMotionVectorX(maxXVelocity);
		setX(position.x + maxXVelocity);
	}
}

void MovableObject::executeMovement(){
	for (Movements currentMovement : currentMovements){
		switch (currentMovement){
		case Movements::RIGHT:
			moveRight();
			break;
		case Movements::LEFT:
			moveLeft();
			break;
		case Movements::JUMP:
			jump();
			break;
		case Movements::PATROL:
			patrol();
			return;
			break;
		case Movements::NONE:
			setMotionVectorX(0.0f);
			break;
		}
	}

	currentMovements.clear();
}

void MovableObject::addMovement(const Movements& movement){
	currentMovements.push_back(movement);
}

void MovableObject::switchPatrolDirection(){
	switch (patrolDirection){
	case 'L':
		patrolDirection = 'R';
		break;
	case 'R':
		patrolDirection = 'L';
		break;
	}
}