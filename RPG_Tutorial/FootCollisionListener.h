#ifndef _FOOTCOLLISIONLISTENER_H
#define _FOOTCOLLISIONLISTENER_H

#include <Box2D\Box2D.h>
#include "Object.h"
#include "MovableObject.h"
#include "SensorId.h"

class FootCollisionListener : public b2ContactListener {

	/// Called when two fixtures begin to touch.
	void BeginContact(b2Contact* contact) {
		SensorId* sensorIdA = (SensorId*)contact->GetFixtureA()->GetUserData();
		CharacterGroup characterGroupA = ((Object*)contact->GetFixtureA()->GetBody()->GetUserData())->getGroup();
		SensorId* sensorIdB = (SensorId*)contact->GetFixtureB()->GetUserData();
		CharacterGroup characterGroupB = ((Object*)contact->GetFixtureB()->GetBody()->GetUserData())->getGroup();

		// Fixture A was the contact?
		if ((characterGroupA == CharacterGroup::MAIN_CHARACTER || characterGroupA == CharacterGroup::MOVABLE_OBJECT) && *sensorIdA == SensorId::FOOT_SENSOR) {
			((MovableObject*)contact->GetFixtureA()->GetBody()->GetUserData())->getFootSensor().incrementContacts();
			std::cout << std::to_string(((MovableObject*)contact->GetFixtureA()->GetBody()->GetUserData())->getFootSensor().getNumOfContacts()) << std::endl;
		}

		// Fixture B was the contact?
		if ((characterGroupB == CharacterGroup::MAIN_CHARACTER || characterGroupB == CharacterGroup::MOVABLE_OBJECT) && *sensorIdB == SensorId::FOOT_SENSOR) {
			((MovableObject*)contact->GetFixtureB()->GetBody()->GetUserData())->getFootSensor().incrementContacts();
			std::cout << std::to_string(((MovableObject*)contact->GetFixtureA()->GetBody()->GetUserData())->getFootSensor().getNumOfContacts()) << std::endl;
		}
	}


	/// Called when two fixtures cease to touch.
	void EndContact(b2Contact* contact) {
		int sensorIdA = (int)contact->GetFixtureA()->GetUserData();
		CharacterGroup characterGroupA = ((Object*)contact->GetFixtureA()->GetBody()->GetUserData())->getGroup();
		int sensorIdB = (int)contact->GetFixtureB()->GetUserData();
		CharacterGroup characterGroupB = ((Object*)contact->GetFixtureB()->GetBody()->GetUserData())->getGroup();

		// Fixture A was the contact?
		if ((characterGroupA == CharacterGroup::MAIN_CHARACTER || characterGroupA == CharacterGroup::MOVABLE_OBJECT) && sensorIdA == SensorId::FOOT_SENSOR) {
			((MovableObject*)contact->GetFixtureA()->GetBody()->GetUserData())->getFootSensor().decrementContacts();
			std::cout << std::to_string(((MovableObject*)contact->GetFixtureA()->GetBody()->GetUserData())->getFootSensor().getNumOfContacts()) << std::endl;
		}

		// Fixture B was the contact?
		if ((characterGroupB == CharacterGroup::MAIN_CHARACTER || characterGroupB == CharacterGroup::MOVABLE_OBJECT) && sensorIdB == SensorId::FOOT_SENSOR) {
			((MovableObject*)contact->GetFixtureB()->GetBody()->GetUserData())->getFootSensor().decrementContacts();
			std::cout << std::to_string(((MovableObject*)contact->GetFixtureA()->GetBody()->GetUserData())->getFootSensor().getNumOfContacts()) << std::endl;
		}
	}
};
#endif