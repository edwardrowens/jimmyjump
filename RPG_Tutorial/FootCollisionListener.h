#ifndef _FOOTCOLLISIONLISTENER_H
#define _FOOTCOLLISIONLISTENER_H

#include <Box2D\Box2D.h>
#include "Object.h"
#include "MovableObject.h"

class FootCollisionListener : public b2ContactListener
{
	/// Called when two fixtures begin to touch.
	void BeginContact(b2Contact* contact) {
		// Fixture A was the contact?
		if (((Object*)contact->GetFixtureA()->GetUserData())->getGroup() == CharacterGroup::MAIN_CHARACTER ||
			((Object*)contact->GetFixtureA()->GetUserData())->getGroup() == CharacterGroup::MOVABLE_OBJECT) {
			((MovableObject*)contact->GetFixtureA()->GetUserData())->getFootSensor().incrementContacts();
		}

		// Fixture A was the contact?
		if (((Object*)contact->GetFixtureB()->GetUserData())->getGroup() == CharacterGroup::MAIN_CHARACTER ||
			((Object*)contact->GetFixtureB()->GetUserData())->getGroup() == CharacterGroup::MOVABLE_OBJECT) {
			((MovableObject*)contact->GetFixtureB()->GetUserData())->getFootSensor().incrementContacts();
		}
	}


	/// Called when two fixtures cease to touch.
	void EndContact(b2Contact* contact) {
		// Fixture A was the contact?
		if (((Object*)contact->GetFixtureA()->GetUserData())->getGroup() == CharacterGroup::MAIN_CHARACTER ||
			((Object*)contact->GetFixtureA()->GetUserData())->getGroup() == CharacterGroup::MOVABLE_OBJECT) {
			((MovableObject*)contact->GetFixtureA()->GetUserData())->getFootSensor().decrementContacts();
		}

		// Fixture B was the contact?
		if (((Object*)contact->GetFixtureB()->GetUserData())->getGroup() == CharacterGroup::MAIN_CHARACTER ||
			((Object*)contact->GetFixtureB()->GetUserData())->getGroup() == CharacterGroup::MOVABLE_OBJECT) {
			((MovableObject*)contact->GetFixtureB()->GetUserData())->getFootSensor().decrementContacts();
		}
	}
};
#endif