#ifndef _BOX2DSERVICE_H
#define _BOX2DSERVICE_H

#include <Box2D\Box2D.h>

class Box2dService {
public:
	const static b2Vec2 retrieveTopLeftVertex(const b2Body &objectBody);
	const static b2Vec2 retrieveBottomRightVertex(const b2Body &objectBody);
	const static b2Vec2 retrieveBottomLeftVertex(const b2Body &objectBody);
	const static b2Vec2 retrieveTopRightVertex(const b2Body &objectBody);
private:
	static const b2Fixture& Box2dService::findNonSensorFixture(const b2Fixture &fixture);
};
#endif

