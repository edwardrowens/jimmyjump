#include "SensorService.h"


b2Fixture SensorService::findSensor(const int &sensorID, b2Fixture &fixture) {
	for (b2Fixture* f = &fixture; f; f->GetNext()) {
		if ((int)f->GetUserData() == sensorID)
			return *f;
	}
}
