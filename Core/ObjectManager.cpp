#include "ObjectManager.h"

ObjectManager::ObjectManager(TextureCache* textureCache) :
textureCache(textureCache),
nextId(0) {

}


void ObjectManager::setContext(SDL_Renderer* context) {
	this->context = context;
}


Object* ObjectManager::createObject(const Character &character, b2Body &objectBody, bool isRenderable) {
	if (character == Character::BACKGROUND) {
		Object* background = new Object(&objectBody, character);
		if (context) {
			background->setIsRenderable(isRenderable);
			if (isRenderable) {
				textureCache->lockTextureForObject(*background);
			}
		}
		background->setId(nextId);
		++nextId;
		objectsInLevel[background->getId()] = background;
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

		objectToAdd->setId(nextId);
		++nextId;

		// Add the object to the cache if we have a context
		if (context) {
			objectToAdd->setIsRenderable(isRenderable);
			if (isRenderable) {
				textureCache->addObjectToCache(*objectToAdd);
			}
		}

		if (objectToAdd) {
			mutey.lock();
			objectsInLevel[objectToAdd->getId()] = objectToAdd;
			mutey.unlock();
		}
		printf("added. %d objects\n", objectsInLevel.size());
		return objectToAdd;
	}
}


/*
Iterates through every object in the level and "locks" their textures. If the texture path has changed
(which for MovableObjects it will) then we want to set the associated texture onto the object so that it will
be drawn to the screen.
*/
void ObjectManager::setTextures() {
	mutey.lock();
	for (int i = 0; i < objectsInLevel.size(); ++i) {
		if (objectsInLevel[i]->getPreviousTexturePath() != objectsInLevel[i]->getTexturePath()) {
			textureCache->lockTextureForObject(*objectsInLevel[i]);
		}
	}
	mutey.unlock();
}


/*
Removes the object from the cache and from the vector which stores all objects in the level.
*/
void ObjectManager::destroyObject(Object &object) {
	if (context) {
		textureCache->removeObjectFromCache(object);
	}

	objectsInLevel.erase(object.getId());
}


MainCharacter& ObjectManager::getPlayableCharacter() {
	return *playableCharacter;
}


void ObjectManager::setPlayableCharacter(MainCharacter& playableCharacter) {
	this->playableCharacter = &playableCharacter;
}


std::map<uint32_t, Object*>& ObjectManager::getObjectsInLevel() {
	return objectsInLevel;
}


void ObjectManager::drawAllObjects() {
	// background color
	SDL_SetRenderDrawColor(context, 0, 0, 0, 0);
	if (SDL_RenderClear(context)) {
		PrintErrors("Renderer failed to clear", SDL_GetError);
	}
	mutey.lock();
	std::map<uint32_t, Object*>::iterator iter = objectsInLevel.begin();
	for (iter; iter != objectsInLevel.end(); ++iter) {
		if (iter->second->getIsRenderable())
			iter->second->draw();
	}
	mutey.unlock();

	SDL_RenderPresent(context);
}


void ObjectManager::putInMotion() {
	std::map<uint32_t, Object*>::iterator iter = objectsInLevel.begin();
	for (iter; iter != objectsInLevel.end(); ++iter) {
		if (iter->second->getIsMovable()) {
			dynamic_cast<MovableObject*>(iter->second)->executeMovement();
		}
	}
}