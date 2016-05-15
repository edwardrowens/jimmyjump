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
		if (((Object*)contact->GetFixtureA()->GetBody()->GetUserData())->getGroup() == CharacterGroup::MAIN_CHARACTER ||
			((Object*)contact->GetFixtureA()->GetBody()->GetUserData())->getGroup() == CharacterGroup::MOVABLE_OBJECT) {
			((MovableObject*)contact->GetFixtureA()->GetBody()->GetUserData())->getFootSensor().incrementContacts();
		}

		// Fixture A was the contact?
		if (((Object*)contact->GetFixtureB()->GetBody()->GetUserData())->getGroup() == CharacterGroup::MAIN_CHARACTER ||
			((Object*)contact->GetFixtureB()->GetBody()->GetUserData())->getGroup() == CharacterGroup::MOVABLE_OBJECT) {
			((MovableObject*)contact->GetFixtureB()->GetBody()->GetUserData())->getFootSensor().incrementContacts();
		}
	}


	/// Called when two fixtures cease to touch.
	void EndContact(b2Contact* contact) {
		// Fixture A was the contact?
		if (((Object*)contact->GetFixtureA()->GetBody()->GetUserData())->getGroup() == CharacterGroup::MAIN_CHARACTER ||
			((Object*)contact->GetFixtureA()->GetBody())->getGroup() == CharacterGroup::MOVABLE_OBJECT) {
			((MovableObject*)contact->GetFixtureA()->GetBody()->GetUserData())->getFootSensor().decrementContacts();
		}

		// Fixture B was the contact?
		if (((Object*)contact->GetFixtureB()->GetBody()->GetUserData())->getGroup() == CharacterGroup::MAIN_CHARACTER ||
			((Object*)contact->GetFixtureB()->GetBody()->GetUserData())->getGroup() == CharacterGroup::MOVABLE_OBJECT) {
			((MovableObject*)contact->GetFixtureB()->GetBody()->GetUserData())->getFootSensor().decrementContacts();
		}
	}
};
#endif