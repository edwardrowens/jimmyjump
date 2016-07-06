#pragma once

#include "Packet.h"

class PacketBatch {
public:
	void addPacket(Packet packet);

	asio::mutable_buffers_1 toAsioBuffer();

	void setClientId(const uint8_t& clientId);
	void setDirective(const uint8_t& directive);
	void setFrame(const uint32_t& frame);
	void setKeyPressesByFrame(const std::map<uint32_t, std::vector<uint8_t>>& keyPressesByFrame);

	uint8_t getClientId() const;
	uint8_t getDirective() const;
	uint32_t getFrame() const;
	std::map<uint32_t, std::vector<uint8_t>>& getKeyPressesByFrame() const;

private:
	enum PacketBatchIndex {
		CLIENT_ID,
		DIRECTIVE,
		FRAME,
		KEY_PRESSES,
		END
	};
	std::vector<uint32_t> data;
};

