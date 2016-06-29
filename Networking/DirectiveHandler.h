#pragma once

#include "Packet.h"
#include "Directives.h"
#include "TheGame.h"

class DirectiveHandler {
public:
	static Packet handleDirective(Packet& packet, TheGame& game);
private:
	static Packet okDirective(Packet& packet, TheGame& game);
	static Packet syncClientDirective(Packet& packet, TheGame& game);
};

