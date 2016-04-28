#include "World.h"


World::World() : 
boxWorld(new b2World(WorldConstants::DEFAULT_GRAVITY)),
objectManager(&textureCache) {
	boxWorld->Step(WorldConstants::UPDATE_TICK, WorldConstants::VELOCITY_ITERATIONS, WorldConstants::POSITION_ITERATIONS);
}


World::~World() {
}


void World::createBody() {
	b2BodyDef objectBodyDefinition;

	objectBodyDefinition.type = b2_dynamicBody;
	objectBodyDefinition.position.Set(250.0f, 250.0f);

	b2Body* objectBody = boxWorld.CreateBody(&objectBodyDefinition);
	b2PolygonShape objectBox;
	objectBox.SetAsBox(25.0f, 10.0f);

	b2FixtureDef objectFixtureDefinition;
	objectFixtureDefinition.density = 1.0f;
	objectFixtureDefinition.shape = &objectBox;
	objectFixtureDefinition.friction = 0.3f;

	objectBody->CreateFixture(&objectFixtureDefinition);
}


void World::setContext(SDL_Renderer* context) {
	objectManager.setContext(context);
	textureCache.setContext(context);
}