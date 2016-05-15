#ifndef _SENSORSERVICE_H
#define _SENSORSERVICE_H

#include <Box2D\Box2D.h>
#include "SensorId.h"

namespace SensorService {
	const b2Fixture findSensor(const SensorId &sensorId, const b2Fixture &fixture);
}

#endif