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

private:
	b2World* boxWorld;
	ObjectManager objectManager;
	TextureCache textureCache;
	SDL_Renderer* context;
};
