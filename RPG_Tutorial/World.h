#pragma once
#include "ObjectManager.h"
#include <Box2D\Box2D.h>
#include "WorldConstants.h"
#include "ObjectPhysicalProperties.h"
#include "Box2dMapper.h"

class World
{
public:
	World();
	~World();

	void setContext(SDL_Renderer* context);

	ObjectManager& getObjectManager();

	Object* createObject(const Character& character, const ObjectPhysicalProperties &props, bool isRenderable);
	void destroyObject(Object* object);
	void applyGravity(const float& gravity);
	void drawAllObjects();
	void updatePreviousPositions();
	void setMousePosition();
	void putInMotion();

private:
	// Fields
	b2World* boxWorld;
	ObjectManager objectManager;
	TextureCache textureCache;
	SDL_Renderer* context;
	
	// Functions
	b2Body& mapToBody(const ObjectPhysicalProperties &props);
};
