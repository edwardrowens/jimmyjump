#pragma once
#include <SDL2.0/SDL.h>
#include "CharacterInformation.h"
#include "CharacterGroupingService.h"
#include "Object.h"
#include "Position.h"
#include <vector>
#include "Utility.h"
#include "MainCharacter.h"
#include "Platform.h"
#include "CollisionDetector.h"
#include "Box2D\Box2D.h"

/*
The entire point of this class is to create instances of objects (factory). This class will ensure that the background is the first instance
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
	void setPlayableCharacter(MainCharacter& playableCharacter);

	// public functions
	Object* createObject(const Character& character, const Position& position, bool isRenderable);
	void destroyObject(Object object);
	void detectCollisions();
	void applyGravity(const float& gravity);
	void drawAllObjects();
	void setTexture(Object& object);
	void setTextures();
	void updatePreviousPositions();
	void setMousePosition() const;
	void putInMotion() const;

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

