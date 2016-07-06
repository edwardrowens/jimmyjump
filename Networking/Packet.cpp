#include "Packet.h"

Packet::Packet() : 
data(PacketIndex::END) {
}


asio::mutable_buffers_1 Packet::toAsioBuffer() {
	return asio::buffer((char*)&data.front(), sizeof(uint32_t) * data.size());
}


void Packet::setObjectId(const uint32_t& objectId) {
	data[PacketIndex::OBJECT_ID] = objectId;
}


void Packet::setXPosition(const uint16_t& xPosition) {
	data[PacketIndex::X_POSITION] = xPosition;
}


void Packet::setYPosition(const uint16_t& yPosition) {
	data[PacketIndex::Y_POSITION] = yPosition;
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