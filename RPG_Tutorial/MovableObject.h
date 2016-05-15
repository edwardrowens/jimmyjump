#ifndef _MOVABLEOBJECT_H
#define _MOVABLEOBJECT_H

#include "Object.h"
#include <math.h>
#include <string>
#include "Movements.h"
#include "CharacterInformation.h"
#include "Box2dService.h"
#include "SensorService.h"
#include "SensorId.h"
#include "Sensor.h"

using std::string;

const float32 MAX_X_VELOCITY = 3.2f;
const float32 MAX_Y_VELOCITY = 5.0f;
const float32 X_VELOCITY_STEP = .8f;
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
	std::vector<Movements> getCurrentMovements() const;
	b2Vec2 getPreviousPosition() const;
	Sensor& getFootSensor();

	// Functions
	void addMovement(const Movements& movement);
	void executeMovement();

	// Fields
	std::vector<Movements> currentMovements;

protected:
	// Functions
	void accelerateLeftward();
	void accelerateRightward();

	// Fields
	int stepCount;

private:
	// Fields
	b2Vec2 maxVelocity;
	b2Vec2 previousPosition;
	Sensor footSensor;

	// Functions
	void jump();
	virtual void moveRight();
	virtual void moveLeft();
};
#endif