#pragma once

#include "Packet.h"
#include "Directives.h"
#include "TheGame.h"
#include <vector>

class DirectiveHandler {
public:
	static std::vector<Packet>& handleDirective(Packet& packet, TheGame& game);
private:
	static std::vector<Packet>& okDirective(Packet& packet, TheGame& game);
	static std::vector<Packet>& syncClientDirective(Packet& packet, TheGame& game);
};

