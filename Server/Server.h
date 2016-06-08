#ifndef SERVER_H
#define SERVER_H

#define ASIO_STANDALONE 
#define ASIO_HAS_STD_ADDRESSOF
#define ASIO_HAS_STD_ARRAY
#define ASIO_HAS_CSTDINT
#define ASIO_HAS_STD_SHARED_PTR
#define ASIO_HAS_STD_TYPE_TRAITS

#include "../dependencies/include/asio/asio.hpp"
#include <iostream>


class Server {
public:
	Server(asio::io_service& asioService);
	~Server();

	void startTCP();

	static const int PORT;
	static const char ADDRESS[];

private:
	asio::io_service &asioService;
};
#endif