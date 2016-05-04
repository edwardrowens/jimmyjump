#include "ObjectManager.h"

ObjectManager::ObjectManager(TextureCache* textureCache) : 
textureCache(textureCache) {

}

// Destructor
ObjectManager::~ObjectManager() {
}


void ObjectManager::setContext(SDL_Renderer* context) {
	this->context = context;
}


Object* ObjectManager::createObject(const Character &character, b2Body &objectBody, bool isRenderable) {
	if (character == Character::BACKGROUND) {
		Object* background = new Object(&objectBody, character);
		objectsInLevel.insert(objectsInLevel.begin(), background);
		(*objectsInLevel[0]).setIsRenderable(isRenderable);
		if (isRenderable) {
			textureCache->lockTextureForObject(*background);
		}
		return objectsInLevel[0];
	}
	else {
		Object* objectToAdd;
		switch (CharacterGroupingService::retrieveCharacterGrouping(character)){
		case CharacterGroup::MAIN_CHARACTER:
			objectToAdd = new MainCharacter(&objectBody, character);
			playableCharacter = dynamic_cast<MainCharacter*>(objectToAdd);
			objectsInLevel.push_back(objectToAdd);
			break;
		case CharacterGroup::MOVABLE_OBJECT:
			objectToAdd = new MovableObject(&objectBody, character);
			objectsInLevel.push_back(objectToAdd);
			break;
		case CharacterGroup::OBJECT:
			objectToAdd = new Object(&objectBody, character);
			objectsInLevel.push_back(objectToAdd);
			break;
		case CharacterGroup::PLATFORM:
			objectToAdd = new Platform(&objectBody, character);
			objectsInLevel.push_back(objectToAdd);
			break;
		}

		// Add the object to the cache
		objectToAdd->setIsRenderable(isRenderable);
		if (isRenderable) {
			textureCache->lockTextureForObject(*objectToAdd);
		}

		return objectToAdd;
	}
}


/*
Iterates through every object in the level and "locks" their textures. If the texture path has changed
(which for MovableObjects it will) then we want to set the associated texture onto the object so that it will
be drawn to the screen.
*/
void ObjectManager::setTextures() {
	for (auto object : objectsInLevel) {
		if (object->getPreviousTexture() != object->getTexture()) {
			textureCache->lockTextureForObject(*object);
		}
	}
}


/*
Removes the object from the cache and from the vector which stores all objects in the level.
*/
void ObjectManager::destroyObject(Object object) {
	textureCache->removeObjectFromCache(object);

	// POTENTIAL SPEED UP: Rethink the data structure which holds the objects in the level as this current algorithm is O(n)
	// whenever we want to remove an object from the game.
	std::vector<Object*>::iterator it = objectsInLevel.begin();
	for (it; it != objectsInLevel.end(); ++it) {
		if ((*it) == &object) {
			delete *it;
			objectsInLevel.erase(it);
		}
	}
}


MainCharacter& ObjectManager::getPlayableCharacter() {
	return *playableCharacter;
}


void ObjectManager::setPlayableCharacter(MainCharacter& playableCharacter) {
	this->playableCharacter = &playableCharacter;
}


void ObjectManager::detectCollisions() {
	std::vector<Object*>::iterator i = objectsInLevel.begin();
	for (i; i != objectsInLevel.end(); ++i) {
		if ((*i)->getIsMovable()) {
			MovableObject* tempObject = dynamic_cast<MovableObject*>(*i);
			CollisionDetector::detectDynamicCollisions(tempObject, objectsInLevel);
			CollisionDetector::detectStaticCollisions(tempObject, objectsInLevel);
		}
	}
}


std::vector<Object*>& ObjectManager::getObjectsInLevel() {
	return objectsInLevel;
}