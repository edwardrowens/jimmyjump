#include "World.h"


World::World() : 
boxWorld(new b2World(WorldConstants::DEFAULT_GRAVITY)),
objectManager(&textureCache) {
	boxWorld->Step(WorldConstants::UPDATE_TICK, WorldConstants::VELOCITY_ITERATIONS, WorldConstants::POSITION_ITERATIONS);
}


World::~World() {
}


Object* World::createObject(const Character& character, const ObjectPhysicalProperties::ObjectPhysicalProperties &props, bool isRenderable) {
	return objectManager.createObject(character, mapToBody(character, props), isRenderable);
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


void World::drawAllObjects() {
	if (SDL_RenderClear(context)) {
		PrintErrors("Renderer failed to clear", SDL_GetError);
	}

	std::vector<Object*>::iterator iter = objectManager.getObjectsInLevel().begin();
	for (iter; iter != objectManager.getObjectsInLevel().end(); ++iter) {
		if ((*iter)->getIsRenderable())
			(*iter)->draw();
	}

	SDL_RenderPresent(context);
}


void World::applyGravity(const float& gravity) {
	std::vector<Object*>::iterator iter = objectManager.getObjectsInLevel().begin();
	for (iter; iter != objectManager.getObjectsInLevel().end(); ++iter) {
		if ((*iter)->getIsMovable()) {
			(*iter)->setY((*iter)->getY() + gravity);
			MovableObject* tmp = (MovableObject*)*iter;
			if (tmp->getGravity() != gravity){
				tmp->setGravity(gravity);
			}
			tmp->setMotionVectorY(tmp->getMotionVectorY() + gravity);
			tmp->setY(tmp->getY() + tmp->getMotionVectorY());
		}
	}
}


/*
Update all previous positions for all MovableObjects in the vector.
*/
void World::updatePreviousPositions() {
	for (auto object : objectManager.getObjectsInLevel()) {
		if (object->getIsMovable()) {
			MovableObject* movable = dynamic_cast<MovableObject*>(object);
			if (movable->getY() == movable->getPreviousXY()[1])
				movable->setIsStable(true);
			else
				movable->setIsStable(false);
			movable->setPreviousXY(movable->getX(), movable->getY());
		}
	}
}


void World::setMousePosition() {
	int mouseX, mouseY;
	SDL_GetMouseState(&mouseX, &mouseY);
	objectManager.getPlayableCharacter().setMousePosition(mouseX, mouseY);
}


void World::putInMotion() {
	for (auto object : objectManager.getObjectsInLevel()) {
		if (object->getIsMovable()) {
			MovableObject* movable = dynamic_cast<MovableObject*>(object);
			movable->executeMovement();
		}
	}
}


b2Body& World::mapToBody(const Character &character, const ObjectPhysicalProperties::ObjectPhysicalProperties &props) {
	b2BodyDef* bodyDef = &Box2dMapper::mapToBody(props);
	b2Body* body = boxWorld->CreateBody(bodyDef);
	b2FixtureDef fixtureDef = Box2dMapper::mapToFixture(props);
	fixtureDef.filter.categoryBits = CollisionCategoryService::retrieveCategoryBits(character);
	fixtureDef.filter.maskBits = CollisionCategoryService::retrieveMaskBits(character);
	b2PolygonShape shapeDef = Box2dMapper::mapToShape(props);
	fixtureDef.shape = &shapeDef;
	body->CreateFixture(&fixtureDef);
	return *body;
}