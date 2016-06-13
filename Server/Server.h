#ifndef SERVER_H
#define SERVER_H

#define ASIO_STANDALONE 
#define ASIO_HAS_STD_ADDRESSOF
#define ASIO_HAS_STD_ARRAY
#define ASIO_HAS_CSTDINT
#define ASIO_HAS_STD_SHARED_PTR
#define ASIO_HAS_STD_TYPE_TRAITS

#include "asio/asio.hpp"
#include <iostream>
#include <map>
#include "boost\bind.hpp"

class Server {
public:
	Server(asio::io_service& asioService);
	~Server();

	void startTCP();
	/*void (Server::*getAcceptHandler)(const asio::error_code&) = &Server::acceptHandler;
	void (Server::*getReadHandler)(const asio::error_code&, std::size_t) = &Server::readHandler;
	void (Server::*getWriteHandler)(const asio::error_code&, std::size_t) = &Server::writeHandler;*/

	static const int PORT;
	static const char ADDRESS[];

private:
	// fields
	asio::io_service &asioService;
	asio::ip::tcp::acceptor acceptor;
	std::map<int, asio::ip::tcp::socket> socketMap;
	asio::ip::tcp::socket socket;
	int nextId;

	// functions
	void readHandler(const asio::error_code &errorCode, std::size_t bytesTransferred);
	void writeHandler(const asio::error_code &errorCode, std::size_t bytesTransferred);
	void acceptHandler(const asio::error_code &errorCode);
};
#endif