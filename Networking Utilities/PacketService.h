#pragma once

#include "Packet.h"
#include "PacketData.h"

class PacketService {
public:
	static PacketData extractPacketData(const Packet& packet);
};

