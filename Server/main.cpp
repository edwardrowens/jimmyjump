#define ASIO_STANDALONE 
#define ASIO_HAS_STD_ADDRESSOF
#define ASIO_HAS_STD_ARRAY
#define ASIO_HAS_CSTDINT
#define ASIO_HAS_STD_SHARED_PTR
#define ASIO_HAS_STD_TYPE_TRAITS
#define BOOST_ALL_DYN_LINK

#include "Server.h"
#include "asio\asio.hpp"
#include "boost\shared_ptr.hpp"

#undef main
int main(int argc, char* argv[]) {
	asio::io_service asioService;
	boost::shared_ptr<Server> server(new Server(asioService));
	server->startTCP();

	return 0;
}