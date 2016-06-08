#define ASIO_STANDALONE 
#define ASIO_HAS_STD_ADDRESSOF
#define ASIO_HAS_STD_ARRAY
#define ASIO_HAS_CSTDINT
#define ASIO_HAS_STD_SHARED_PTR
#define ASIO_HAS_STD_TYPE_TRAITS

#include <iostream>
#include <exception>
#include <array>
#include <string>
#include <ctime>
#include "asio.hpp"

using namespace std;

void accept_handler(const asio::error_code ec) {
	if (!ec) {
		printf("%d\n", ec.value());
		printf("A connection has been made\n");
	}
}

void asioTcpServer() {
		asio::io_service aios;
		asio::ip::tcp::acceptor acceptor(aios, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), 8080));
		std::cout << "Server ready" << std::endl;
	for(;;) {
		asio::ip::tcp::socket socket(aios);
		acceptor.listen();
		acceptor.async_accept(socket, accept_handler);
		aios.run();
	}
}


int main(int argc, char* argv[]) {
	asioTcpServer();
}