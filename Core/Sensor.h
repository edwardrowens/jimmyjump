#ifndef _SENSOR_H
#define _SENSOR_H

#include <Box2D\Box2D.h>

class Sensor {
public:
	Sensor(const b2Fixture &fixture);

	void incrementContacts();
	void decrementContacts();
	const int& getNumOfContacts() const;

private:
	int numOfContacts;
	const b2Fixture* fixture;
};
#endif