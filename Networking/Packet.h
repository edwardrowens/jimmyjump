#pragma once

#include "asio\asio.hpp"
#include <vector>
#include "PacketService.h"

class Packet {
public:
	Packet();

	asio::mutable_buffers_1 toAsioBuffer();
	void setObjectId(const uint32_t& objectId);
	void setXPosition(const uint16_t& xPosition);
	void setYPosition(const uint16_t& yPosition);

	uint32_t getObjectId() const;
	uint16_t getXPosition() const;
	uint16_t getYPosition() const;
private:
	enum PacketIndex {
		OBJECT_ID,
		X_POSITION,
		Y_POSITION,
		END
	};
	std::vector<uint32_t> data;
};