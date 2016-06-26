#ifndef CLIENT_H
#define CLIENT_H

#define ASIO_STANDALONE 
#define ASIO_HAS_STD_ADDRESSOF
#define ASIO_HAS_STD_ARRAY
#define ASIO_HAS_CSTDINT
#define ASIO_HAS_STD_SHARED_PTR
#define ASIO_HAS_STD_TYPE_TRAITS

#include "asio\asio.hpp"
#include "boost\bind.hpp"
#include "boost\enable_shared_from_this.hpp"
#include <vector>
#include "TheGame.h"
#include "boost\thread.hpp"
#include "Packet.h"

class Client : public boost::enable_shared_from_this<Client> {
public:
	Client(asio::io_service& asioService);

	void start(std::string address, std::string port);
	void kill(); 

private:
	// fields
	uint16_t id;
	asio::ip::tcp::socket socket;
	asio::ip::tcp::resolver resolver;
	asio::ip::tcp::resolver::iterator endpoint;
	asio::io_service& asioService;
	std::unique_ptr<std::vector<uint16_t>> readBuffer;
	std::unique_ptr<std::vector<uint16_t>> writeBuffer;
	TheGame game;

	// functions
	void connectHandler(asio::error_code errorCode, asio::ip::tcp::resolver::iterator resolverIter);
	void readHandler(asio::error_code errorCode, std::size_t bytesTransferred);
	void initialReadHandler(asio::error_code errorCode, std::size_t bytesTransferred);
	void writeHandler(asio::error_code errorCode, std::size_t bytesTransferred);
	void connectToServer(std::string address, std::string port);
	void readFromServer();
	void sendObjectPositions();
};
#endif