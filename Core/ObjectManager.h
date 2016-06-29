#pragma once
#include <SDL2.0/SDL.h>
#include "CharacterInformation.h"
#include "CharacterGroupingService.h"
#include "Object.h"
#include "Position.h"
#include <vector>
#include <map>
#include "Utility.h"
#include "MainCharacter.h"
#include "Platform.h"
#include "Box2D\Box2D.h"
#include "TextureCache.h"
#include <mutex>

/*
The entire point of this class is to create instances of objects (factory). This class will ensure that the background is the first instance
that is input into the objectsInLevel pointer vector and will handle all the caching. Think of it like god, deciding the fate of an
object.
*/
using std::string;

class ObjectManager {
public:
	// constructors/destructors
	ObjectManager(TextureCache* textureCache);

	// Getters
	MainCharacter& getPlayableCharacter();
	void setPlayableCharacter(MainCharacter& playableCharacter);

	// public functions
	Object* createObject(const Character& character, b2Body& objectBody, bool isRenderable);
	void destroyObject(Object &object);
	void setTextures();
	void setContext(SDL_Renderer* context);
	void drawAllObjects();
	std::map<uint32_t, Object*>& getObjectsInLevel();
	void putInMotion();

private:
	// Fields
	SDL_Renderer* context;
	std::map<uint32_t, Object*> objectsInLevel;
	Utility utility;
	TextureCache* textureCache;
	MainCharacter* playableCharacter;
	std::mutex mutey;
	Uint32 nextId;

	// Functions
	void deleteTextures(Character character);
};

