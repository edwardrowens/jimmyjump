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


	void add(T element) {
		data.push_back(element);
	}

	std::vector<T>& getData() {
		return data;
	}

private:
	std::vector<T> data;
	Uint8 id;
};