#include "PacketBatch.h"


asio::mutable_buffers_1 PacketBatch::toAsioBuffer() {

}


void PacketBatch::setClientId(const uint8_t& clientId) {
	data[PacketBatchIndex::CLIENT_ID] = clientId;
}


void PacketBatch::setDirective(const uint8_t& directive) {
	data[PacketBatchIndex::DIRECTIVE] = directive;
}


void PacketBatch::setFrame(const uint32_t& frame) {
	data[PacketBatchIndex::FRAME] = frame;
}


void PacketBatch::setKeyPressesByFrame(const std::map<uint32_t, std::vector<uint8_t>>& keyPressesByFrame) {
	data.insert(data.begin() + PacketBatchIndex::END, keyPressesByFrame.begin(), keyPressesByFrame.end());
}


uint8_t PacketBatch::getClientId() const {
	return data[PacketBatchIndex::CLIENT_ID];
}


uint8_t PacketBatch::getDirective() const {
	return data[PacketBatchIndex::DIRECTIVE];
}


uint32_t PacketBatch::getFrame() const {
	return data[PacketBatchIndex::FRAME];
}