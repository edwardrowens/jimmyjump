#include "MovableObject.h"

// Position and character constructor.
MovableObject::MovableObject(b2Body* objectBody, Character character) :
Object(objectBody, character),
stepCount(0),
maxVelocity(b2Vec2(MAX_X_VELOCITY, MAX_Y_VELOCITY)),
footSensor(Sensor(SensorService::findSensor(SensorId::FOOT_SENSOR, *objectBody->GetFixtureList()))),
timeOfLastJump(0) {
	objectBody->SetFixedRotation(true);
	group = CharacterGroup::MOVABLE_OBJECT;
	isMovable = true;
}

MovableObject::MovableObject(const MovableObject &movableObject) :
Object(movableObject),
stepCount(0),
maxVelocity(b2Vec2(MAX_X_VELOCITY, MAX_Y_VELOCITY)),
footSensor(Sensor(SensorService::findSensor(SensorId::FOOT_SENSOR, *objectBody->GetFixtureList()))) {
}

MovableObject::~MovableObject() {
}

// PROBLEM: does not include fields unique to MovableObject's
MovableObject& MovableObject::operator=(const MovableObject &moveableObject) {
	Object::operator=(moveableObject);

	return *this;
}


std::vector<Movements> MovableObject::getCurrentMovements() const {
	return currentMovements;
}


void MovableObject::jump() {
	int timeElapsedSinceLastJump = SDL_GetTicks() - timeOfLastJump;
	if (footSensor.getNumOfContacts() > 0 && timeElapsedSinceLastJump > 250) {
		float impulse = objectBody->GetMass() * 10.0f;
		objectBody->ApplyLinearImpulse(b2Vec2(0, impulse), objectBody->GetWorldCenter(), true);
		timeOfLastJump = SDL_GetTicks();
	}
}


void MovableObject::moveRight() {
	accelerateRightward();

	if (stepCount >= walkCycles['R'].size()) {
		stepCount = 0;
	}

	// POTENTIAL PROBLEM: If I use another type of file for textures, I would have to make a more general solution rather than
	// hard-coding this string.
	std::string texturePath = getTexturePath();
	int fileLocInPath = utility.getFileLocFromPath(texturePath);
	char firstCharInFileName = texturePath.substr(fileLocInPath, texturePath.size())[0];

	// This checks if they have a directionality in their image files. If they don't, then we don't want to see their texturePath to
	// an invalid file.
	if (firstCharInFileName == 'R' || firstCharInFileName == 'L') {
		texturePath = texturePath.substr(0, fileLocInPath);
		texturePath = texturePath + "R" + std::to_string(stepCount) + ".png";
	}

	setTexturePath(texturePath);

	++stepCount;
}


void MovableObject::moveLeft() {
	accelerateLeftward();

	if (stepCount >= walkCycles['L'].size()) {
		stepCount = 0;
	}

	// POTENTIAL PROBLEM: If I use another type of file for textures, I would have to make a more general solution rather than
	// hard-coding this string.
	std::string texturePath = getTexturePath();
	int fileLocInPath = utility.getFileLocFromPath(texturePath);
	char firstCharInFileName = texturePath.substr(fileLocInPath, texturePath.size())[0];

	// This checks if they have a directionality in their image files. If they don't, then we don't want to see their texturePath to
	// an invalid file.
	if (firstCharInFileName == 'L' || firstCharInFileName == 'R') {
		texturePath = texturePath.substr(0, fileLocInPath);
		texturePath = texturePath + "L" + std::to_string(stepCount) + ".png";
	}

	setTexturePath(texturePath);

	++stepCount;
}


void MovableObject::accelerateLeftward() {
	b2Vec2 bodyVelocity = objectBody->GetLinearVelocity();
	float32 newVelocity = b2Max(bodyVelocity.x - X_VELOCITY_STEP, -MAX_X_VELOCITY);
	float32 deltaVelocity = newVelocity - bodyVelocity.x;
	float32 impulse = objectBody->GetMass() * deltaVelocity;
	objectBody->ApplyLinearImpulse(b2Vec2(impulse, 0), objectBody->GetWorldCenter(), true);
}


void MovableObject::accelerateRightward() {
	b2Vec2 bodyVelocity = objectBody->GetLinearVelocity();
	float32 deltaVelocity = b2Min(bodyVelocity.x + X_VELOCITY_STEP, MAX_X_VELOCITY);
	float32 newVelocity = deltaVelocity - bodyVelocity.x;
	float32 impulse = objectBody->GetMass() * newVelocity;
	objectBody->ApplyLinearImpulse(b2Vec2(impulse, 0), objectBody->GetWorldCenter(), true);
}


void MovableObject::executeMovement() {
	for (Movements currentMovement : currentMovements) {
		switch (currentMovement) {
		case Movements::RIGHT:
			moveRight();
			break;
		case Movements::LEFT:
			moveLeft();
			break;
		case Movements::JUMP:
			jump();
			break;
		case Movements::NONE:
			objectBody->SetLinearVelocity(b2Vec2(0.0f, objectBody->GetLinearVelocity().y));
			break;
		}
	}

	// We've executed all movements in the buffer, so let's clear out the buffer now.
	currentMovements.clear();
}


void MovableObject::addMovement(const Movements& movement) {
	currentMovements.push_back(movement);
}


Sensor& MovableObject::getFootSensor() {
	return footSensor;
}