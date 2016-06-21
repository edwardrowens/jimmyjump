#define ASIO_STANDALONE 
#define ASIO_HAS_STD_ADDRESSOF
#define ASIO_HAS_STD_ARRAY
#define ASIO_HAS_CSTDINT
#define ASIO_HAS_STD_SHARED_PTR
#define ASIO_HAS_STD_TYPE_TRAITS

#include "Client.h"
#include "asio\asio.hpp"
#include "boost\shared_ptr.hpp"
#undef main //shitty SDL defines main for initialization...

int main(int argc, char* argv[]) {
	asio::io_service asioService;
	boost::shared_ptr<Client> client(new Client(asioService));
	client->start("localhost", "8080");
	system("PAUSE");
}