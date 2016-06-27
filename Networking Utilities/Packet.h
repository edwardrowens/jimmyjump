#pragma once

#include "asio\asio.hpp"
#include <vector>

template<typename T>
class Packet {
public:
	asio::mutable_buffers_1 toAsioBuffer() {
		if (data.empty()) {
			T t;
			data.emplace_back(t);
		}

		return asio::buffer((char*)&data.front(), sizeof(T) * data.size());
	}


	void setClientId(const Uint8& clientId) {
		this->clientId = clientId;
	}

	
	void setDirective(const Uint8& directive) {
		this->directive = directive;
	}


	void setObjectId(const Uint32& objectId) {
		this->objectId = objectId;
	}


	void setXPosition(const Uint8& xPosition)

private:
	std::vector<T> data;
	Uint8 clientId, directive, xPosition, yPosition;
	Uint32 objectId;
};