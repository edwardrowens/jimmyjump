#include "SensorService.h"


const b2Fixture SensorService::findSensor(const SensorId &sensorID, const b2Fixture &fixture) {
	for (const b2Fixture* f = &fixture; f; f->GetNext()) {
		if (*(SensorId*) f->GetUserData() == sensorID)
			return *f;
	}
}
