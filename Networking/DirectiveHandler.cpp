#include "DirectiveHandler.h"

//std::vector<Packet>& DirectiveHandler::handleDirective(Packet& packet, TheGame& game) {
//	switch ((Directives)packet.getDirective()) {
//	case Directives::OK:
//		okDirective(packet, game);
//		break;
//	case Directives::CLIENT_SYNC:
//		syncClientDirective(packet, game);
//		break;
//	case Directives::SERVER_SYNC:
//		break;
//	}
//}
//
//
//static std::vector<Packet>& okDirective(Packet& packet, TheGame& game) {
//	std::unique_ptr<std::vector<Packet>> packetPtr(new std::vector<Packet>(1));
//	(*packetPtr)[0] = packet;
//	return *packetPtr;
//}
//
//
//static std::vector<Packet>& syncClientDirective(Packet& packet, TheGame& game) {
//}