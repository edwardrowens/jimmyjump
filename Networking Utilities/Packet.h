#pragma once

#include "asio\asio.hpp"
#include <vector>

template<typename T>
class Packet {
public:
	asio::mutable_buffers_1 toAsioBuffer() {
		return asio::buffer((char*)&data.front(), sizeof(T) * data.size());
	}

	void add(T element) {
		data.push_back(element);
	}
private:
	std::vector<T> data;
};

