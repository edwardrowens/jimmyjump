#include "Box2dService.h"

const b2Fixture& Box2dService::findNonSensorFixture(const b2Fixture &fixture) {
	for (const b2Fixture* f = &fixture; f; f = f->GetNext()) {
		if (!f->IsSensor())
			return *f;
	}
}

const b2Vec2 Box2dService::retrieveTopLeftVertex(const b2Body &objectBody) {
	return objectBody.GetWorldPoint(dynamic_cast<const b2PolygonShape*>(findNonSensorFixture(*objectBody.GetFixtureList()).GetShape())->GetVertex(3));
}


const b2Vec2 Box2dService::retrieveBottomRightVertex(const b2Body &objectBody) {
	return objectBody.GetWorldPoint(dynamic_cast<const b2PolygonShape*>(findNonSensorFixture(*objectBody.GetFixtureList()).GetShape())->GetVertex(1));
}


const b2Vec2 Box2dService::retrieveBottomLeftVertex(const b2Body &objectBody) {
	return objectBody.GetWorldPoint(dynamic_cast<const b2PolygonShape*>(findNonSensorFixture(*objectBody.GetFixtureList()).GetShape())->GetVertex(0));
}


const b2Vec2 Box2dService::retrieveTopRightVertex(const b2Body &objectBody) {
	return objectBody.GetWorldPoint(dynamic_cast<const b2PolygonShape*>(findNonSensorFixture(*objectBody.GetFixtureList()).GetShape())->GetVertex(2));
}


const b2Vec2 Box2dService::retrieveTopLeftVertex(const b2Body &objectBody, const b2Fixture &fixture) {
	return objectBody.GetWorldPoint(dynamic_cast<const b2PolygonShape*>(fixture.GetShape())->GetVertex(3));
}


const b2Vec2 Box2dService::retrieveBottomRightVertex(const b2Body &objectBody, const b2Fixture &fixture) {
	return objectBody.GetWorldPoint(dynamic_cast<const b2PolygonShape*>(fixture.GetShape())->GetVertex(1));
}


const b2Vec2 Box2dService::retrieveBottomLeftVertex(const b2Body &objectBody, const b2Fixture &fixture) {
	return objectBody.GetWorldPoint(dynamic_cast<const b2PolygonShape*>(fixture.GetShape())->GetVertex(0));
}


const b2Vec2 Box2dService::retrieveTopRightVertex(const b2Body &objectBody, const b2Fixture &fixture) {
	return objectBody.GetWorldPoint(dynamic_cast<const b2PolygonShape*>(fixture.GetShape())->GetVertex(2));
}


const float32 Box2dService::getNonSensorFixtureWorldHeight(const b2Body &objectBody) {
	return std::abs(retrieveTopLeftVertex(objectBody).y - retrieveBottomRightVertex(objectBody).y);
}


const float32 Box2dService::getNonSensorFixtureWorldWidth(const b2Body &objectBody) {
	return std::abs(retrieveTopLeftVertex(objectBody).x - retrieveBottomRightVertex(objectBody).x);
}


const int Box2dService::getNonSensorFixtureScreenHeight(const b2Body &objectBody) {
	return getNonSensorFixtureWorldHeight(objectBody) * WorldConstants::PIXELS_PER_METER;
}


const int Box2dService::getNonSensorFixtureScreenWidth(const b2Body &objectBody) {
	return getNonSensorFixtureWorldWidth(objectBody) * WorldConstants::PIXELS_PER_METER;
}


const int Box2dService::getFixtureScreenHeight(const b2Body &objectBody, const b2Fixture &fixture) {
	return getFixtureWorldHeight(objectBody, fixture) * WorldConstants::PIXELS_PER_METER;
}


const int Box2dService::getFixtureScreenWidth(const b2Body &objectBody, const b2Fixture &fixture) {
	return getFixtureWorldWidth(objectBody, fixture) * WorldConstants::PIXELS_PER_METER;
}


const int Box2dService::getFixtureWorldHeight(const b2Body &objectBody, const b2Fixture &fixture) {
	return std::abs(retrieveTopLeftVertex(objectBody, fixture).y - retrieveBottomLeftVertex(objectBody, fixture).y);
}


const int Box2dService::getFixtureWorldWidth(const b2Body &objectBody, const b2Fixture &fixture) {
	return std::abs(retrieveTopRightVertex(objectBody, fixture).x - retrieveTopLeftVertex(objectBody, fixture).x);
}