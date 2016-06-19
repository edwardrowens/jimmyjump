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
#include <vector>
#include "boost\bind.hpp"
#include "boost\enable_shared_from_this.hpp"
#include "boost\shared_ptr.hpp"
#include "TheGame.h"

class Server : public boost::enable_shared_from_this<Server> {
public:
	Server(asio::io_service& asioService);

	void startTCP();
	void addClient();
	void startUpdateLoop();

	static const int PORT;
	static const char ADDRESS[];

private:
	// fields
	asio::io_service &asioService;
	asio::ip::tcp::acceptor acceptor;
	std::map<int, asio::ip::tcp::socket> socketMap;
	asio::ip::tcp::socket socket;
	int nextId;
	std::unique_ptr<std::vector<uint16_t>> readBuffer;
	std::unique_ptr<std::vector<uint16_t>> writeBuffer;

	// functions
	void readHandler(const asio::error_code &errorCode, std::size_t bytesTransferred, int clientId);
	void writeHandler(const asio::error_code &errorCode, std::size_t bytesTransferred, int clientId);
	void acceptHandler(const asio::error_code &errorCode);

	void assignAndSendClientId();
};
#endif