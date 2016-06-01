#define ASIO_STANDALONE 
#define ASIO_HAS_STD_ADDRESSOF
#define ASIO_HAS_STD_ARRAY
#define ASIO_HAS_CSTDINT
#define ASIO_HAS_STD_SHARED_PTR
#define ASIO_HAS_STD_TYPE_TRAITS

#include <iostream>
#include <exception>
#include <array>
#include "../dependencies/include/asio/asio.hpp"

using namespace std;

void asioTcpServer() {
	asio::io_service aios;
	asio::ip::tcp::acceptor acceptor(aios, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), 8080));
	std::cout << "Server ready" << std::endl;
	asio::ip::tcp::socket socket(aios);
	acceptor.accept(socket);
	cout << "Connection made to: " + socket.remote_endpoint().address().to_string() << endl;
	cout << "Port: " + to_string(socket.remote_endpoint().port()) << endl;
}


int main(int argc, char* argv[]) {
	asioTcpServer();
}