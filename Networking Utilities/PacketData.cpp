#include "PacketData.h"


PacketData::PacketData() {
}


uint8_t PacketData::getClientId() const {
	return clientId;
}


uint8_t PacketData::getDirective() const {
	return directive;
}


uint32_t PacketData::getObjectId() const {
	return objectId;
}


DWORD PacketData::getFrame() const {
	return frame;
}


uint16_t PacketData::getXPosition() const {
	return xPosition;
}


uint16_t PacketData::getYPosition() const {
	return yPosition;
}


void PacketData::setClientId(const uint8_t& clientId) {
	this->clientId = clientId;
}


void PacketData::setDirective(const uint8_t& directive) {
	this->directive = directive;
}


void PacketData::setObjectId(const uint32_t& objectId) {
	this->objectId = objectId;
}


void PacketData::setFrame(const DWORD& frame) {
	this->frame = frame;
}


void PacketData::setXPosition(const uint16_t& xPosition) {
	this->xPosition = xPosition;
}


void PacketData::setYPosition(const uint16_t& yPosition) {
	this->yPosition = yPosition;
}