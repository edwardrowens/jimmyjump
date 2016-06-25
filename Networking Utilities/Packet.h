#pragma once

#include "asio\asio.hpp"
#include <vector>

template<typename T>
class Packet {
public:
	asio::mutable_buffer toAsioBuffer();
	void add(T element);
private:
	std::vector<T> data;
};

