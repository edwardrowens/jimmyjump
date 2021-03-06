#ifndef _FOOTCOLLISIONLISTENER_H
#define _FOOTCOLLISIONLISTENER_H

#include <Box2D\Box2D.h>
#include "Object.h"
#include "MovableObject.h"
#include "SensorId.h"

class FootCollisionListener : public b2ContactListener {

	/// Called when two fixtures begin to touch.
	void BeginContact(b2Contact* contact) {
		SensorId* sensorIdA = static_cast<SensorId*>(contact->GetFixtureA()->GetUserData());
		Object* objectA = (Object*)contact->GetFixtureA()->GetBody()->GetUserData();

		SensorId* sensorIdB = static_cast<SensorId*>(contact->GetFixtureB()->GetUserData());
		Object* objectB = (Object*)contact->GetFixtureB()->GetBody()->GetUserData();

		// Fixture A was the contact?
		if (objectA->getIsMovable() && sensorIdA && *sensorIdA == SensorId::FOOT_SENSOR) {
			((MovableObject*) objectA)->getFootSensor().incrementContacts();
		}

		// Fixture B was the contact?
		if (objectB->getIsMovable() && sensorIdB && *sensorIdB == SensorId::FOOT_SENSOR) {
			((MovableObject*) objectB)->getFootSensor().incrementContacts();
		}
	}


	/// Called when two fixtures cease to touch.
	void EndContact(b2Contact* contact) {
		SensorId* sensorIdA = (SensorId*)contact->GetFixtureA()->GetUserData();
		Object* objectA = (Object*)contact->GetFixtureA()->GetBody()->GetUserData();

		SensorId* sensorIdB = (SensorId*)contact->GetFixtureB()->GetUserData();
		Object* objectB = (Object*)contact->GetFixtureB()->GetBody()->GetUserData();

		// Fixture A was the contact?
		if (objectA->getIsMovable() && sensorIdA && *sensorIdA == SensorId::FOOT_SENSOR) {
			((MovableObject*) objectA)->getFootSensor().decrementContacts();
		}

		// Fixture B was the contact?
		if (objectB->getIsMovable() && sensorIdB && *sensorIdB == SensorId::FOOT_SENSOR) {
			((MovableObject*) objectB)->getFootSensor().decrementContacts();
		}
	}
};
#endif