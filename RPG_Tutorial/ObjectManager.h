#pragma once
#include <SDL2.0/SDL.h>
#include "CharacterInformation.h"
#include "Object.h"
#include "Position.h"
#include <vector>
#include "Utility.h"
#include "MainCharacter.h"
#include "Platform.h"
#include "CollisionDetector.h"

/*
The entire point of this class is to create instances of objects. This class will ensure that the background is the first instance
that is input into the objectsInLevel pointer vector and will handle all the caching. Think of it like god, deciding the fate of an
object.
*/
using std::string;

class ObjectManager{
public:
	// constructors/destructors
	ObjectManager();
	ObjectManager(SDL_Renderer* context, MainCharacter* playableCharacter);
	~ObjectManager();

	// Getters
	MainCharacter* getPlayableCharacter() const;

	// public functions
	Object createObject(const Character& character, const Position& position, bool isRenderable);
	void destroyObject(Object object);
	CharacterGrouping retrieveCharacterGrouping(const Character& character);
	void detectCollisions();
	void applyGravity(const int& gravity);
	void drawAllObjects();
	void setObjectTexture(Object& object);

private:
	// Fields
	SDL_Renderer* context;
	std::vector<Object*> objectsInLevel;
	std::map<Character, int> amountOfObjects;
	Utility utility;
	std::hash_map<string, SDL_Texture*> textureCache;
	MainCharacter* playableCharacter;

	// Functions
	void initializeAmountOfObjects();
	void deleteTextures(Character character);
};

