#ifndef _BOX2DSERVICE_H
#define _BOX2DSERVICE_H

#include <Box2D\Box2D.h>
#include "WorldConstants.h"

class Box2dService {
public:
	// Finds the vertices for the non sensor fixture.
	const static b2Vec2 retrieveTopLeftVertex(const b2Body &objectBody);
	const static b2Vec2 retrieveBottomRightVertex(const b2Body &objectBody);
	const static b2Vec2 retrieveBottomLeftVertex(const b2Body &objectBody);
	const static b2Vec2 retrieveTopRightVertex(const b2Body &objectBody);

	// Fixture overload - finds the vertices on the specified fixture.
	// Body is only required to get the vertex points in relation to the world (annoying)
	const static b2Vec2 retrieveTopLeftVertex(const b2Body &objectBody, const b2Fixture &fixture);
	const static b2Vec2 retrieveBottomRightVertex(const b2Body &objectBody, const b2Fixture &fixture);
	const static b2Vec2 retrieveBottomLeftVertex(const b2Body &objectBody, const b2Fixture &fixture);
	const static b2Vec2 retrieveTopRightVertex(const b2Body &objectBody, const b2Fixture &fixture);

	const static int getNonSensorFixtureScreenHeight(const b2Body &objectBody);
	const static int getNonSensorFixtureScreenWidth(const b2Body &objectBody);
	const static float32 getNonSensorFixtureWorldHeight(const b2Body &objectBody);
	const static float32 getNonSensorFixtureWorldWidth(const b2Body &objectBody);

	const static int getFixtureScreenHeight(const b2Body &objectBody, const b2Fixture &fixture);
	const static int getFixtureScreenWidth(const b2Body &objectBody, const b2Fixture &fixture);
private:
	const static b2Fixture& findNonSensorFixture(const b2Fixture &fixture);
};
#endif

