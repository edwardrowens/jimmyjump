#include "Box2dService.h"


b2Vec2 Box2dService::retrieveTopLeftVertex(const b2Body &objectBody) {
	return objectBody.GetWorldPoint(dynamic_cast<const b2PolygonShape*>(findNonSensorFixture(*objectBody.GetFixtureList()).GetShape())->GetVertex(3));
}


b2Vec2 Box2dService::retrieveBottomRightVertex(const b2Body &objectBody) {
	return objectBody.GetWorldPoint(dynamic_cast<const b2PolygonShape*>(findNonSensorFixture(*objectBody.GetFixtureList()).GetShape())->GetVertex(1));
}


b2Vec2 Box2dService::retrieveBottomLeftVertex(const b2Body &objectBody) {
	return objectBody.GetWorldPoint(dynamic_cast<const b2PolygonShape*>(findNonSensorFixture(*objectBody.GetFixtureList()).GetShape())->GetVertex(0));
}


b2Vec2 Box2dService::retrieveTopRightVertex(const b2Body &objectBody) {
	return objectBody.GetWorldPoint(dynamic_cast<const b2PolygonShape*>(findNonSensorFixture(*objectBody.GetFixtureList()).GetShape())->GetVertex(2));
}


const b2Fixture& findNonSensorFixture(const b2Fixture &fixture) {
	for (const b2Fixture* f = &fixture; f; f->GetNext())
		if (!f->IsSensor())
			return *f;
}