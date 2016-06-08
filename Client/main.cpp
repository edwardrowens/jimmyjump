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

void asioTcpClient() {
	asio::io_service aios;
	asio::ip::tcp::socket socket(aios);
	asio::ip::tcp::resolver resolver(aios); // 1
	asio::ip::tcp::resolver::iterator endpoint = resolver.resolve(
		asio::ip::tcp::resolver::query("localhost", HELLO_PORT_STR));
	asio::connect(socket, endpoint);
}


int main(int argc, char* argv[]) {
	asioTcpClient();
	system("PAUSE");
}