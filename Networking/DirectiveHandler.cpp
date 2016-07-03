#include "DirectiveHandler.h"

std::unique_ptr<std::vector<Packet>> DirectiveHandler::handleDirective(Packet& packet, TheGame& game) {
	switch ((Directives)packet.getDirective()) {
	case Directives::OK:
		okDirective(packet);
		break;
	case Directives::CLIENT_SYNC:
		syncClientDirective(packet.getClientId(), game);
		break;
	case Directives::SERVER_SYNC:
		syncServerDirective(packet, game);
		break;
	}
}


std::unique_ptr<std::vector<Packet>> DirectiveHandler::okDirective(Packet& packet) {
	std::unique_ptr<std::vector<Packet>> packetPtr(new std::vector<Packet>(1));
	(*packetPtr)[0] = packet;
	return packetPtr;
}


std::unique_ptr<std::vector<Packet>> DirectiveHandler::syncClientDirective(const uint8_t& clientId, TheGame& game) {
	std::unique_ptr<std::vector<Packet>> packetBatch(new std::vector<Packet>);
	std::vector<uint32_t> objectKeys = game.getWorld().getAllObjectKeys();

	// synchronize the playable character's input first
	for (auto objectKey : objectKeys) {
		Packet packet;
		packet.setClientId(clientId);
		packet.setDirective(Directives::NONE);
		packet.setFrame(game.getUpdateTick());
		packet.setObjectId(objectKey);
		packet.setXPosition(game.getWorld().getObject(objectKey)->getX());
		packet.setYPosition(game.getWorld().getObject(objectKey)->getY());
		packetBatch->push_back(packet);
	}

	return packetBatch;
}


std::unique_ptr<std::vector<Packet>> DirectiveHandler::syncServerDirective(Packet& packet, TheGame& game) {

}