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
		background->setIsRenderable(isRenderable);
		if (isRenderable) {
			textureCache->lockTextureForObject(*background);
		}
		objectsInLevel.insert(objectsInLevel.begin(), background);
		return background;
	}
	else {
		Object* objectToAdd = nullptr;
		switch (CharacterGroupingService::retrieveCharacterGrouping(character)){
		case CharacterGroup::MAIN_CHARACTER:
			objectToAdd = new MainCharacter(&objectBody, character);
			playableCharacter = dynamic_cast<MainCharacter*>(objectToAdd);
			break;
		case CharacterGroup::MOVABLE_OBJECT:
			objectToAdd = new MovableObject(&objectBody, character);
			break;
		case CharacterGroup::OBJECT:
			objectToAdd = new Object(&objectBody, character);
			break;
		case CharacterGroup::PLATFORM:
			objectToAdd = new Platform(&objectBody, character);
			break;
		}

		// Add the object to the cache
		objectToAdd->setIsRenderable(isRenderable);
		if (isRenderable) {
			textureCache->addObjectToCache(*objectToAdd);
		}

		if (objectToAdd) {
			mutey.lock();
			objectsInLevel.push_back(objectToAdd);
			mutey.unlock();
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
	for (int i = 0; i < objectsInLevel.size(); ++i) {
		if (objectsInLevel[i]->getPreviousTexturePath() != objectsInLevel[i]->getTexturePath()) {
			textureCache->lockTextureForObject(*objectsInLevel[i]);
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


std::vector<Object*>& ObjectManager::getObjectsInLevel() {
	return objectsInLevel;
}


void ObjectManager::drawAllObjects() {
	// background color
	SDL_SetRenderDrawColor(context, 0, 0, 0, 0);
	if (SDL_RenderClear(context)) {
		PrintErrors("Renderer failed to clear", SDL_GetError);
	}
	for (int i = 0; i < getObjectsInLevel().size(); ++i) {
		if (getObjectsInLevel()[i]->getIsRenderable())
			getObjectsInLevel()[i]->draw();
	}

	SDL_RenderPresent(context);
}