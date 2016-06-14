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
#include "Server.h"
#include "asio\asio.hpp"

using namespace std;

void acceptHandler(const asio::error_code ec) {
	if (!ec) {
		printf("A connection has been made\n");
	}
	else {
		printf("Connection attempted\n.");
	}
}

void readHandler(const asio::error_code ec, std::size_t bytesTransferred) {
	if (bytesTransferred > 0)
		printf("Data received by server\n");
	else if (ec.value() == asio::error::eof) {
		printf("The connection has closed\n");
	}
}

void asioTcpServer() {
	asio::io_service aios;
	asio::ip::tcp::acceptor acceptor(aios, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), 8080));
	std::cout << "Server ready" << std::endl;
	asio::ip::tcp::socket socket(aios);
	for (;;) {
		acceptor.listen();
		acceptor.async_accept(socket, acceptHandler);
		std::vector<uint16_t> net(3, 0);
		asio::async_read(socket, asio::buffer((char*)&net.front(), 6), readHandler);
		aios.run();
	}
}


int main(int argc, char* argv[]) {
	asio::io_service asioService;
	Server server(asioService);
	server.startTCP();
}