#pragma once
#include "ObjectManager.h"
#include <Box2D\Box2D.h>
#include"WorldConstants.h"

class World
{
public:
	World();
	~World();

	void createBody();
	void setContext(SDL_Renderer* context);

	ObjectManager& getObjectManager();

	Object* createObject(const Character& character, const b2Body& objectBody, bool isRenderable);
	void destroyObject(Object* object);

private:
	b2World* boxWorld;
	ObjectManager objectManager;
	TextureCache textureCache;
	SDL_Renderer* context;
};
