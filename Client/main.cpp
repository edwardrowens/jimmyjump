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
	if (!errorCode) {
		printf("Write successful. Bytes transferred: %d\n", bytesTransferred);
	}
	else {
		printf("Write failed! %s (%d)\n", errorCode.message().c_str(), errorCode.value());
	}
}

void connectHandler(asio::error_code errorCode, asio::ip::tcp::resolver::iterator resolverIter) {
	if (!errorCode) {
		printf("Client connected successfully\n");
	}
	else {
		printf("Client connection failed! %s (%d)\n", errorCode.message().c_str(), errorCode.value());
	}
}

void asioTcpClient() {
	asio::io_service aios;
	asio::ip::tcp::socket socket(aios);
	asio::ip::tcp::resolver resolver(aios); // 1
	asio::ip::tcp::resolver::iterator endpoint = resolver.resolve(
		asio::ip::tcp::resolver::query("localhost", HELLO_PORT_STR));
	asio::async_connect(socket, endpoint, connectHandler);
	aios.run();
	//asio::connect(socket, endpoint);
	vector<uint16_t> net(1);
	//asio::async_write(socket, asio::buffer((char*)&net.front(), 2), writeHandler);
	//aios.run();
}


int main(int argc, char* argv[]) {
	asioTcpClient();
	system("PAUSE");
}