#include "Packet.h"

Packet::Packet() : 
data(PacketIndex::END),
xPosition(-1),
yPosition(-1),
clientId(-1),
objectId(-1),
directive(-1) {
}


asio::mutable_buffers_1 Packet::toAsioBuffer() {
	data[PacketIndex::CLIENT_ID] = clientId;
	data[PacketIndex::DIRECTIVE] = directive;
	data[PacketIndex::OBJECT_ID] = objectId;
	data[PacketIndex::X_POSITION] = xPosition;
	data[PacketIndex::Y_POSITION] = yPosition;
	data[PacketIndex::FRAME] = frame;

	return asio::buffer((char*)&data.front(), sizeof(uint32_t) * PacketIndex::END);
}


void Packet::setClientId(const uint8_t& clientId) {
	this->clientId = clientId;
}


void Packet::setDirective(const uint8_t& directive) {
	this->directive = directive;
}


void Packet::setObjectId(const uint32_t& objectId) {
	this->objectId = objectId;
}


void Packet::setXPosition(const uint16_t& xPosition) {
	this->xPosition = xPosition;
}


void Packet::setYPosition(const uint16_t& yPosition) {
	this->yPosition = yPosition;
}


uint8_t Packet::getClientId() const {
	return data[PacketIndex::CLIENT_ID];
}


uint8_t Packet::getDirective() const {
	return data[PacketIndex::DIRECTIVE];
}


uint32_t Packet::getObjectId() const {
	return data[PacketIndex::OBJECT_ID];
}


uint16_t Packet::getXPosition() const {
	return data[PacketIndex::X_POSITION];
}


uint16_t Packet::getYPosition() const {
	return data[PacketIndex::Y_POSITION];
}


DWORD Packet::getFrame() const {
	return data[PacketIndex::FRAME];
}