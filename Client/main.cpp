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
#include <ctime>

namespace {
	const char* HELLO_PORT_STR = "8080";
}

using namespace std;

void writeHandler(asio::error_code errorCode, size_t bytesTransferred) {
	printf("Writing %d bytes to the server\n", bytesTransferred);
}

void connectHandler(asio::error_code errorCode, asio::ip::tcp::resolver::iterator resolverIter) {
}

void asioTcpClient() {
	asio::io_service aios;
	asio::ip::tcp::socket socket(aios);
	asio::ip::tcp::resolver resolver(aios); // 1
	asio::ip::tcp::resolver::iterator endpoint = resolver.resolve(
		asio::ip::tcp::resolver::query("localhost", HELLO_PORT_STR));
	asio::async_connect(socket, endpoint, connectHandler);
	//asio::connect(socket, endpoint);
	vector<uint16_t> net(3, 0);
	net[0] = 1;
	net[1] = 2;
	net[2] = 3;
	asio::async_write(socket, asio::buffer((char*)&net.front(), 6), writeHandler);
	aios.run();
}


int main(int argc, char* argv[]) {
	asioTcpClient();
	system("PAUSE");
}