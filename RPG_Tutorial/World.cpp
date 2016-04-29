#include "World.h"


World::World() : 
boxWorld(new b2World(WorldConstants::DEFAULT_GRAVITY)),
objectManager(&textureCache) {
	boxWorld->Step(WorldConstants::UPDATE_TICK, WorldConstants::VELOCITY_ITERATIONS, WorldConstants::POSITION_ITERATIONS);
}


World::~World() {
}


Object* World::createObject(const Character& character, const b2Body& objectBody, bool isRenderable) {
	return objectManager.createObject(character, objectBody, isRenderable);
}


void World::destroyObject(Object* object) {
	boxWorld->DestroyBody(object->getBody());
	objectManager.destroyObject(*object);
}


void World::setContext(SDL_Renderer* context) {
	objectManager.setContext(context);
	textureCache.setContext(context);
}


ObjectManager& World::getObjectManager() {
	return objectManager;
}