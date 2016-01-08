#include "ObjectManager.h"

// Default constructor
ObjectManager::ObjectManager() : context(nullptr){
	initializeAmountOfObjects();
}

// Context constructor
ObjectManager::ObjectManager(SDL_Renderer* context, MainCharacter* playableCharacter) : 
context(context), 
playableCharacter(playableCharacter){
	initializeAmountOfObjects();
}

// Destructor
ObjectManager::~ObjectManager(){
}

/*
TODO - Everything is currently an object rather than a platform or whatever.
*/
Object ObjectManager::createObject(const Character &character, const Position &position, bool isRenderable){
	if (objectsInLevel.size() <= 1 && character != Character::BACKGROUND){
		PrintErrors("The background must be added prior to any other characters.");
	}
	++amountOfObjects[character];

	objectsInLevel.push_back(new Object(position, character));
	(*objectsInLevel[objectsInLevel.size() - 1]).setIsRenderable(isRenderable);
	if (isRenderable){
		setObjectTexture(*objectsInLevel[objectsInLevel.size() - 1]);
	}

	return *objectsInLevel[objectsInLevel.size() - 1];
}

/*
Map that keeps track of the amount of a certain character on a map in the given level.
*/
void ObjectManager::initializeAmountOfObjects(){
	for (int i = Character::BEGINNING + 1; i < Character::END; ++i){
		Character cmp = (Character)i;
		amountOfObjects[cmp] = 0;
	}
}

void ObjectManager::setObjectTexture(Object &object){
	if (context == nullptr){
		PrintErrors("The context passed in was null. A texture cannot be set without a context.");
	}
	// cannot be found in map
	if (textureCache.find(object.getTexturePath()) == textureCache.end()){
		SDL_Texture* texture = IMG_LoadTexture(context, object.getTexturePath().c_str());
		if (texture == nullptr){
			PrintErrors(object.getTexturePath() + " did not load properly! Make sure the path is correct.");
		}
		else{
			object.setObjectTexture(texture);
		}
		textureCache.insert(std::pair<std::string, SDL_Texture*>(object.getTexturePath(), object.getObjectTexture()));
	}
	else{
		object.setObjectTexture(textureCache[object.getTexturePath()]);
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

MainCharacter* ObjectManager::getPlayableCharacter() const{
	return playableCharacter;
}