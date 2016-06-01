#ifndef	_CONVERSIONSERVICE_H
#define _CONVERSIONERVICE_H

#include <Box2D\Box2D.h>
#include "WorldConstants.h"
#include "Box2dService.h"

namespace ConversionService {
	b2Vec2 screenPointToWorldPoint(const int &x, const int &y);
	b2Vec2 worldPointToScreenPoint(const float32 &x, const float32 &y);
	b2Vec2 screenPointToWorldPoint(const b2Vec2 &point);
	b2Vec2 worldPointToScreenPoint(const b2Vec2 &point);
	float32 screenValueToWorldValue(const int &value);
	int worldValueToScreenValue(const float32 &value);
	b2Vec2 retrieveRenderingRectangleForNonSensorFixture(const b2Body &objectBody, const int &width, const int &height);
}
#endif