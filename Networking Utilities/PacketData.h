#pragma once

#include "asio\asio.hpp"
#include <vector>

class PacketData {
public:
	PacketData();
	~PacketData();

private:
	uint8_t clientId, position, directive;
	uint32_t objectId;
	DWORD frame;
};

