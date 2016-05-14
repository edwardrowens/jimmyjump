#ifndef _SENSORSERVICE_H
#define _SENSORSERVICE_H

#include <Box2D\Box2D.h>

namespace SensorService {
	b2Fixture findSensor(const int &sensorId, b2Fixture &fixture);
}

#endif