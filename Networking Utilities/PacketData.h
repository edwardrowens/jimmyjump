#pragma once

#include "asio\asio.hpp"
#include <vector>

class PacketData {
public:
	PacketData();

	void setClientId(const uint8_t& clientId);
	void setDirective(const uint8_t& directive);
	void setObjectId(const uint32_t& objectId);
	void setFrame(const DWORD& frame);
	void setXPosition(const uint16_t& xPosition);
	void setYPosition(const uint16_t& yPosition);

	uint8_t getClientId() const;
	uint8_t getDirective() const;
	uint32_t getObjectId() const;
	DWORD getFrame() const;
	uint16_t getXPosition() const;
	uint16_t getYPosition() const;

private:
	uint8_t clientId, directive;
	uint16_t xPosition, yPosition;
	uint32_t objectId;
	DWORD frame;
};

