#pragma once

#include "Packet.h"

class DirectiveHandler {
public:
	static Packet handleDirective(Packet& packet, TheGame& game);
};

