#ifndef _BOX2DSERVICE_H
#define _BOX2DSERVICE_H

#include <Box2D\Box2D.h>

namespace Box2dService {
	b2Vec2 retrieveTopLeftVertex(const b2Body &objectBody);
	b2Vec2 retrieveBottomRightVertex(const b2Body &objectBody);
	b2Vec2 retrieveBottomLeftVertex(const b2Body &objectBody);
	b2Vec2 retrieveTopRightVertex(const b2Body &objectBody);
}
#endif

