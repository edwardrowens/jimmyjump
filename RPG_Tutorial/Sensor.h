#ifndef _SENSOR_H
#define _SENSOR_H

#include <Box2D\Box2D.h>

class Sensor {
public:
	const static int ID = 1;

	Sensor(b2Fixture &fixture);

	void incrementContacts();
	void decrementContacts();
	const int& getNumOfContacts() const;

private:
	int numOfContacts;
	b2Fixture* fixture;
};
#endif