#include "Packet.h"

Packet::Packet() : 
data(PacketIndex::END) {
}


asio::mutable_buffers_1 Packet::toAsioBuffer() {
	return asio::buffer((char*)&data.front(), sizeof(uint32_t) * data.size());
}


void Packet::setClientId(const uint8_t& clientId) {
	data[PacketIndex::CLIENT_ID] = clientId;
}


void Packet::setDirective(const uint8_t& directive) {
	data[PacketIndex::DIRECTIVE] = directive;
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


void Packet::setFrame(const uint32_t& frame) {
	data[PacketIndex::FRAME] = frame;
}


void Packet::setKeyPressesByFrame(const std::map<uint32_t, std::vector<uint8_t>>& keyPressesByFrame) {
	data.insert(data.begin() + PacketIndex::END, keyPressesByFrame.begin(), keyPressesByFrame.end());
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


uint32_t Packet::getFrame() const {
	return data[PacketIndex::FRAME];
}