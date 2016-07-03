#pragma once

#include "Packet.h"
#include "Directives.h"
#include "TheGame.h"
#include <vector>

class DirectiveHandler {
public:
	static std::unique_ptr<std::vector<Packet>> handleDirective(Packet& packet, TheGame& game);
private:
	static std::unique_ptr<std::vector<Packet>> okDirective(Packet& packet);
	static std::unique_ptr<std::vector<Packet>> syncClientDirective(const uint8_t& clientId, TheGame& game);
	static std::unique_ptr<std::vector<Packet>> syncServerDirective(Packet& packet, TheGame& game);
};

