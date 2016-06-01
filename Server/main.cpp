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

void accept_handler() {
	std::time_t now = std::time(nullptr);
	data = std::ctime(&now);
	asio::async_write(asio::ip::tcp_socket, asio::buffer(data), write_handler);
}

void asioTcpServer() {
	asio::io_service aios;
	asio::ip::tcp::acceptor acceptor(aios, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), 8080));
	std::cout << "Server ready" << std::endl;
	asio::ip::tcp::socket socket(aios);
	acceptor.listen();
	acceptor.async_accept(socket, accept_handler);
	cout << "Connection made to: " + socket.remote_endpoint().address().to_string() << endl;
	cout << "Port: " + to_string(socket.remote_endpoint().port()) << endl;
}


int main(int argc, char* argv[]) {
	asioTcpServer();
}