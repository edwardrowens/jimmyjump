#include "MovableObject.h"


//initiating stats to arbitrary values
MovableObject::MovableObject() : _health(100.0f), _strength(10.0f), _speed(5),
_isStable(true), _previousXYPosition(new int[2]),_hitbox(new SDL_Rect()),
_currentMovement(Movements::none){
	_isMovable = true;
	_previousXYPosition[0] = _x;
	_previousXYPosition[1] = _y;
}

MovableObject::MovableObject(int x, int y, int width, int height) : Object(x, y, width, height), _health(100.0f),
_strength(10.0f), _speed(5), _isStable(true), _hitbox(new SDL_Rect), _previousXYPosition(new int[2]),
_currentMovement(Movements::none){
	_isMovable = true;
	_hitbox->x = HITBOX_MODIFIER*_x;
	_hitbox->y = HITBOX_MODIFIER*_y;
	_hitbox->w = HITBOX_MODIFIER*_width;
	_hitbox->h = HITBOX_MODIFIER*_height;
	_previousXYPosition[0] = _x;
	_previousXYPosition[1] = _y;
}

MovableObject::MovableObject(const MovableObject &movableObject): Object(movableObject),
_previousXYPosition(new int[2]), _hitbox(new SDL_Rect), _currentMovement(Movements::none){
	*(_hitbox) = *(movableObject.getHitbox());
	_previousXYPosition[0] = _x;
	_previousXYPosition[1] = _y;
}

MovableObject::~MovableObject(){
	delete _hitbox;
	delete _previousXYPosition;
}

MovableObject& MovableObject::operator=(const MovableObject &moveableObject){
	Object::operator=(moveableObject);
	SDL_Rect* movableRect = moveableObject.getHitbox();
	this->_hitbox->x = movableRect->x;
	this->_hitbox->y = movableRect->y;
	this->_hitbox->w = movableRect->w;
	this->_hitbox->h = movableRect->h;

	return *this;
}



float MovableObject::getStrength() const{
	return _strength;
}

float MovableObject::getHealth() const{
	return _health;
}

int MovableObject::getSpeed() const{
	return _speed;
}


bool MovableObject::getIsStable() const{
	return _isStable;
}

SDL_Rect* MovableObject::getHitbox() const{
	return _hitbox;
}

MovableObject::Movements MovableObject::getCurrentMovement() const{
	return _currentMovement;
}

MovableObject::Movements MovableObject::getPreviousMovement() const{
	return _previousMovement;
}

int* MovableObject::getPreviousXY() const{
	return _previousXYPosition;
}

void MovableObject::setStrength(float newStrength){
	_strength = newStrength;
}

void MovableObject::setHealth(float newHealth){
	_health = newHealth;
}

void MovableObject::setSpeed(int newSpeed){
	_speed = newSpeed;
}


void MovableObject::setIsStable(bool isStable){
	_isStable = isStable;
}

void MovableObject::setWidth(int width){
	Object::setWidth(width);
	_hitbox->w = HITBOX_MODIFIER*width;
}

void MovableObject::setHeight(int height){
	Object::setHeight(height);
	_hitbox->h = HITBOX_MODIFIER*height;
}

void MovableObject::setX(int x){
	Object::setX(x);
	_hitbox->x = HITBOX_MODIFIER*x;
}

void MovableObject::setY(int y){
	Object::setY(y);
	_hitbox->y = HITBOX_MODIFIER*y;
}

void MovableObject::setCurrentMovement(Movements movements){
	_currentMovement = movements;
}

void MovableObject::setPreviousMovement(Movements movements){
	_previousMovement = movements;
}

void MovableObject::setPreviousXY(int x, int y){
	_previousXYPosition[0] = x;
	_previousXYPosition[1] = y;
}


void MovableObject::jump(){
	setY(_y - 10);
	_currentMovement = Movements::jump;
}

void MovableObject::moveRight(){
	setX(_x += _speed);
	_currentMovement = Movements::right;
}

void MovableObject::moveLeft(){
	setX(_x -= _speed);
	_currentMovement = Movements::left;
}

void MovableObject::useItem(){

}

float MovableObject::attack(){
	return _strength;
}

float MovableObject::calcAngleOfMovement() const{
	float deltaY = _y - _previousXYPosition[1];
	float deltaX = _previousXYPosition[0] - _x;

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
	float deltaY = _y - _previousXYPosition[1];
	float deltaX = _previousXYPosition[0] - _x;

	if (deltaX == 0.0f){
		return 0;
	}

	return (deltaY / deltaX);
}
