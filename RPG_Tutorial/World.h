#ifndef _WORLD_H
#define _WORLD_H

#include "ObjectManager.h"
#include <Box2D\Box2D.h>
#include "WorldConstants.h"
#include "ObjectPhysicalProperties.h"
#include "Box2dMapper.h"
#include "CollisionCategory.h"

class World
{
public:
	World();
	~World();

	void setContext(SDL_Renderer* context);

	ObjectManager& getObjectManager();

	Object* createObject(const Character& character, const ObjectPhysicalProperties::ObjectPhysicalProperties &props, bool isRenderable);
	void destroyObject(Object* object);
	void drawAllObjects();
	void step();

private:
	// Fields
	b2World* boxWorld;
	ObjectManager objectManager;
	TextureCache textureCache;
	SDL_Renderer* context;
	
	// Functions
	void putInMotion();
	void setMousePosition();
	b2Body& mapToBody(const Character &character, const ObjectPhysicalProperties::ObjectPhysicalProperties &props);
};
#endif
