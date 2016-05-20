#include "SensorService.h"


const b2Fixture SensorService::findSensor(const SensorId &sensorID, const b2Fixture &fixture) {
	for (const b2Fixture* f = &fixture; f; f = f->GetNext()) {
		SensorId* sensorId = (SensorId*)f->GetUserData();
		if (sensorId && *sensorId == sensorID)
			return *f;
	}
}
