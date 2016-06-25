#include "Packet.h"

template<typename T>
asio::mutable_buffer Packet<T>::toAsioBuffer() {
	return asio::buffer((char*)&data->front(), sizeof(T) * data.size());
}


template<typename T>
void Packet<T>::add(T element) {
	data.push_back(element);
}