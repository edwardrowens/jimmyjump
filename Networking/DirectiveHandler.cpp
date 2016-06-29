#include "DirectiveHandler.h"

Packet DirectiveHandler::handleDirective(Packet& packet, TheGame& game) {
	switch ((Directives)packet.getDirective()) {
	case Directives::OK:
		okDirective(packet, game);
		break;
	case Directives::CLIENT_SYNC:
		syncClientDirective(packet, game);
		break;
	}
}


static Packet okDirective(Packet& packet, TheGame& game) {
	return packet;
}


static Packet syncClientDirective(Packet& packet, TheGame& game) {
}