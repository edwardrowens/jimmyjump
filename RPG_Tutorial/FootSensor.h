#ifndef _FOOTSENSOR_H
#define _FOOTSENSOR_H

#include "Sensor.h"
#include <Box2D\Box2D.h>

class FootSensor : public Sensor {
public:
	FootSensor(b2Fixture &footFixture);
};
#endif