#ifndef	_COORDINATESERVICE_H
#define _COORDINATESERVICE_H

#include <Box2D\Box2D.h>
#include "WorldConstants.h"

namespace CoordinateService {
	b2Vec2 worldToScreen(const float &x, const float &y);
	b2Vec2 screenToWorld(const int &x, const int &y);
}
#endif