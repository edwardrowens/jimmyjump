#include "World.h"


World::World() :
boxWorld(new b2World(WorldConstants::DEFAULT_GRAVITY)),
objectManager(&textureCache) {
	this->boxWorld->SetContactListener(&footCollisionListener);
	boxWorld->SetDebugDraw(&debugger);
	debugger.SetFlags(DebugDraw::e_shapeBit);
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
	debugger.setContext(context);
}



ObjectManager& World::getObjectManager() {
	return objectManager;
}


/*
Sets the textures for every object and draws them.
*/
void World::drawAllObjects() {
	getObjectManager().setTextures();
	getObjectManager().drawAllObjects();
}


void World::setMousePosition() {
	int mouseX, mouseY;
	SDL_GetMouseState(&mouseX, &mouseY);
	objectManager.getPlayableCharacter().setMousePosition(mouseX, mouseY);
}


void World::step() {
	setMousePosition();
	putInMotion();
	boxWorld->Step(WorldConstants::UPDATE_TICK, WorldConstants::VELOCITY_ITERATIONS, WorldConstants::POSITION_ITERATIONS);
	boxWorld->DrawDebugData();
}


void World::putInMotion() {
	for (auto object : objectManager.getObjectsInLevel()) {
		if (object->getGroup() == CharacterGroup::MOVABLE_OBJECT || object->getGroup() == CharacterGroup::MAIN_CHARACTER) {
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

	if (character == Character::JIM) {
		b2FixtureDef footFixtureDef;
		b2PolygonShape footShapeDef;
		footShapeDef.SetAsBox(props.w * .05f, props.h * .05f, b2Vec2(props.x, props.y + (props.h * .05f)), 0.0f);
		footFixtureDef.isSensor = true;
		footFixtureDef.shape = &footShapeDef;
		footFixtureDef.userData = (void*)SensorId::FOOT_SENSOR;
		body->CreateFixture(&footFixtureDef);
	}

	body->ResetMassData();
	return *body;
}