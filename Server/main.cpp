#define ASIO_STANDALONE 
#define ASIO_HAS_STD_ADDRESSOF
#define ASIO_HAS_STD_ARRAY
#define ASIO_HAS_CSTDINT
#define ASIO_HAS_STD_SHARED_PTR
#define ASIO_HAS_STD_TYPE_TRAITS

#include "asio\asio.hpp"
#include <iostream>

int main(int argc, char* argv[]) {
	asio::io_service ioService;
	printf("hi\n");
	return 0;
}