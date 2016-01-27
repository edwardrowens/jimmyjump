#include "ObjectManager.h"

// Default constructor
ObjectManager::ObjectManager() : context(nullptr){
	initializeAmountOfObjects();
}

// Context and main character constructor
ObjectManager::ObjectManager(SDL_Renderer* context, MainCharacter* playableCharacter) :
context(context),
playableCharacter(playableCharacter){
	initializeAmountOfObjects();
	objectsInLevel.push_back(playableCharacter);
	setTexture(*playableCharacter);
}

// Destructor
ObjectManager::~ObjectManager(){
}

/*
TODO - Everything is currently an object rather than a platform or whatever.
*/
Object ObjectManager::createObject(const Character &character, const Position &position, bool isRenderable){
	if (character == Character::BACKGROUND){
		if (amountOfObjects[character] == 0){
			objectsInLevel.insert(objectsInLevel.begin(), new Object(position, character));
			(*objectsInLevel[0]).setIsRenderable(isRenderable);
			if (isRenderable){
				setTexture(*objectsInLevel[0]);
			}
			return *objectsInLevel[0];
		}
		else{
			PrintErrors("There can only be a single background per level.");
		}
	}
	else{
		CharacterGrouping characterGrouping = retrieveCharacterGrouping(character);
		switch (characterGrouping){
		case CharacterGrouping::MAIN_CHARACTER:
			objectsInLevel.push_back(new MainCharacter(position, character));
			break;
		case CharacterGrouping::MOVABLE_OBJECT:
			objectsInLevel.push_back(new MovableObject(position, character));
			break;
		case CharacterGrouping::OBJECT:
			objectsInLevel.push_back(new Object(position, character));
			break;
		case CharacterGrouping::PLATFORM:
			objectsInLevel.push_back(new Platform(position, character));
			break;
		}

		(*objectsInLevel[objectsInLevel.size() - 1]).setIsRenderable(isRenderable);
		if (isRenderable){
			setTexture(*objectsInLevel[objectsInLevel.size() - 1]);
		}

		return *objectsInLevel[objectsInLevel.size() - 1];
	}
}

/*
Map that keeps track of the amount of a characters in the current level.
*/
void ObjectManager::initializeAmountOfObjects(){
	for (int i = Character::BEGINNING + 1; i < Character::END; ++i){
		Character cmp = (Character)i;
		amountOfObjects[cmp] = 0;
	}
}

void ObjectManager::setTextures(){
	for (auto object : objectsInLevel){
		if (object->getPreviousTexture() != object->getTexture()){
			setTexture(*object);
		}
	}
}

void ObjectManager::setTexture(Object &object){
	if (context == nullptr){
		PrintErrors("The context passed in was null. A texture cannot be set without a context.");
	}
	++amountOfObjects[object.getCharacter()];
	object.setContext(context);
	// cannot be found in cache
	if (textureCache.find(object.getTexturePath()) == textureCache.end()){
		SDL_Texture* texture = IMG_LoadTexture(context, object.getTexturePath().c_str());
		if (texture == nullptr){
			PrintErrors(object.getTexturePath() + " did not load properly! Make sure the path is correct.");
		}
		else{
			object.setTexture(texture);
		}
		textureCache.insert(std::pair<std::string, SDL_Texture*>(object.getTexturePath(), object.getTexture()));
	}
	else{
		object.setTexture(textureCache[object.getTexturePath()]);
	}
}

void ObjectManager::deleteTextures(Character character){
	if (amountOfObjects[character] <= 0){
		PrintErrors("A character with " + std::to_string(amountOfObjects[character]) + " associated textures were going to be removed from the cache");
	}
	else if (character == Character::NONE){
		return;
	}
	else if (utility.isPng(utility.getCharacterToFileMap()[character])){
		SDL_DestroyTexture(textureCache[utility.getCharacterToFileMap()[character]]);
		textureCache.erase(utility.getCharacterToFileMap()[character]);
	}
	else{
		std::list<string> pngs = utility.findAllPngs(utility.getCharacterToFileMap()[character]);
		for (string file : pngs){
			SDL_DestroyTexture(textureCache[utility.getCharacterToFileMap()[character] + file]);
			textureCache.erase(utility.getCharacterToFileMap()[character] + file);
		}
	}
}

/*
Removes the object from the cache and from the vector which stores all objects in the level.
*/
void ObjectManager::destroyObject(Object object){
	--amountOfObjects[object.getCharacter()];
	if (amountOfObjects[object.getCharacter()] <= 0){
		deleteTextures(object.getCharacter());
	}

	// POTENTIAL SPEED UP: Rethink the data structure which holds the objects in the level as this current algorithm is O(n)
	// whenever we want to remove an object from the game.
	std::vector<Object*>::iterator it = objectsInLevel.begin();
	for (it; it != objectsInLevel.end(); ++it){
		if ((*it) == &object){
			delete *it;
			objectsInLevel.erase(it);
		}
	}
}

CharacterGrouping ObjectManager::retrieveCharacterGrouping(const Character& character){
	switch (character){
	case Character::NONE:
		return CharacterGrouping::OBJECT;
		break;
	case Character::BACKGROUND:
		return CharacterGrouping::OBJECT;
		break;
	case Character::FLYING_HEART_LARGE:
		return CharacterGrouping::MOVABLE_OBJECT;
		break;
	case Character::FLYING_HEART_SMALL:
		return CharacterGrouping::MOVABLE_OBJECT;
		break;
	case Character::JIM:
		return CharacterGrouping::MAIN_CHARACTER;
		break;
	case Character::LIGHT_GRAY_PLATFORM:
		return CharacterGrouping::PLATFORM;
		break;
	case Character::LIGHT_GREEN_PLATFORM:
		return CharacterGrouping::PLATFORM;
		break;
	}
}

MainCharacter* ObjectManager::getPlayableCharacter() const{
	return playableCharacter;
}

void ObjectManager::detectCollisions(){
	std::vector<Object*>::iterator i = objectsInLevel.begin();
	for (i; i != objectsInLevel.end(); ++i){
		if ((*i)->getIsMovable()){
			MovableObject* tempObject = dynamic_cast<MovableObject*>(*i);
			CollisionDetector::detectStaticCollisions(tempObject, objectsInLevel);
			CollisionDetector::detectDynamicCollisions(tempObject, objectsInLevel);
		}
	}
}

void ObjectManager::applyGravity(const float& gravity){
	std::vector<Object*>::iterator iter = objectsInLevel.begin();
	for (iter; iter != objectsInLevel.end(); ++iter){
		if ((*iter)->getIsMovable()){
			(*iter)->setY((*iter)->getY() + gravity);
			MovableObject* tmp = (MovableObject*)*iter;
			if (tmp->getGravity() != gravity){
				tmp->setGravity(gravity);
			}
		}
	}
}

void ObjectManager::drawAllObjects(){
	if (SDL_RenderClear(context)){
		PrintErrors("Renderer failed to clear", SDL_GetError);
	}

	std::vector<Object*>::iterator iter = objectsInLevel.begin();
	for (iter; iter != objectsInLevel.end(); ++iter){
		if ((*iter)->getIsRenderable())
			(*iter)->draw();
	}

	SDL_RenderPresent(context);
}

/*
Update all previous positions for all MovableObjects in the vector.
*/
void ObjectManager::updatePreviousPositions(){
	for (auto object : objectsInLevel){
		if (object->getIsMovable()){
			MovableObject* movable = dynamic_cast<MovableObject*>(object);
			if (movable->getY() == movable->getPreviousXY()[1])
				movable->setIsStable(true);
			else
				movable->setIsStable(false);
			movable->setPreviousXY(movable->getX(), movable->getY());
		}
	}
}

void ObjectManager::setMousePosition() const{
	int mouseX, mouseY;
	SDL_GetMouseState(&mouseX, &mouseY);
	playableCharacter->setMousePosition(mouseX, mouseY);
}