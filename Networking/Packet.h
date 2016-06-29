#pragma once

#include "asio\asio.hpp"
#include <vector>

class Packet {
public:
	Packet();

	asio::mutable_buffers_1 toAsioBuffer();
	void setClientId(const uint8_t& clientId);
	void setDirective(const uint8_t& directive);
	void setObjectId(const uint32_t& objectId);
	void setXPosition(const uint16_t& xPosition);
	void setYPosition(const uint16_t& yPosition);
	void setFrame(const DWORD& frame);
	void setKeyPressesByFrame(const std::map<DWORD, std::vector<uint8_t>>& keyPressesByFrame);

	uint8_t getClientId() const;
	uint8_t getDirective() const;
	uint32_t getObjectId() const;
	uint16_t getXPosition() const;
	uint16_t getYPosition() const;
	DWORD getFrame() const;
	std::map<DWORD, std::vector<uint8_t>>& getKeyPressesByFrame() const;
private:
	enum PacketIndex {
		CLIENT_ID,
		DIRECTIVE,
		OBJECT_ID,
		FRAME,
		X_POSITION,
		Y_POSITION,
		KEY_PRESSES,
		END
	};
	std::vector<DWORD> data;
	uint8_t clientId, directive;
	uint16_t xPosition, yPosition;
	uint32_t objectId;
	DWORD frame;
	std::map<DWORD, std::vector<uint8_t>> keyPressesByFrame;
};