#include "PacketService.h"

PacketData extractPacketData(const Packet& packet) {
	PacketData packetData;
	packetData.setClientId(packet.getClientId());
	packetData.setObjectId(packet.getObjectId());
	packetData.setDirective(packet.getDirective());
	packetData.setFrame(packet.getFrame());
	packetData.setXPosition(packet.getXPosition());
	packetData.setYPosition(packet.getYPosition());
}