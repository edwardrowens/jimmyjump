#include "Sensor.h"

Sensor::Sensor(const b2Fixture &fixture) :
fixture(&fixture),
numOfContacts(0) {

}


void Sensor::incrementContacts() {
	++numOfContacts;
}


void Sensor::decrementContacts() {
	--numOfContacts;
}


const int& Sensor::getNumOfContacts() const {
	return numOfContacts;
}