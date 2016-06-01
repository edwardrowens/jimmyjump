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

namespace {
	const char* HELLO_PORT_STR = "8080";
}

void asioTcpClient(const char* host) {
	try {
		asio::io_service aios;

		asio::ip::tcp::resolver resolver(aios);
		asio::ip::tcp::resolver::iterator endpoint = resolver.resolve(asio::ip::tcp::resolver::query(host, HELLO_PORT_STR));
		asio::ip::tcp::socket socket(aios);
		// open the connection for the specified endpoint, or throws a system_error
		asio::connect(socket, endpoint);

		for (;;) {
			std::array<char, 4> buf;
			asio::error_code error;
			size_t len = socket.read_some(asio::buffer(buf), error);

			if (error == asio::error::eof)
				break; // Connection closed cleanly by peer
			else if (error)
				throw asio::system_error(error);
			
			std::cout.write(buf.data(), len);
			std::cout << '|';
		}
		std::cout << std::endl;
	}
	catch (std::exception& e) {
		std::cerr << e.what() << std::endl;
	}
}


int main(int argc, char* argv[]) {
	asioTcpClient("localhost");
	system("PAUSE");
}