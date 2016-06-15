#include "Client.h"

Client::Client(asio::io_service& asioService) :
asioService(asioService),
socket(asioService),
resolver(asioService) {
}


void Client::connectToServer(std::string address, std::string port) {
	endpoint = resolver.resolve(asio::ip::tcp::resolver::query(address, port));
	asio::async_connect(socket, endpoint, boost::bind(&Client::connectHandler, shared_from_this(), _1, _2));
	asioService.run();
	retrieveIdFromServer();
}


void Client::connectHandler(asio::error_code errorCode, asio::ip::tcp::resolver::iterator resolverIter) {
	if (!errorCode) {
		printf("Client connected successfully\n");
	}
	else {
		printf("Client connection failed! %s (%d)\n", errorCode.message().c_str(), errorCode.value());
	}
}


void Client::initialReadHandler(asio::error_code errorCode, std::size_t bytesTransferred) {
	if (!errorCode && bytesTransferred == 2) {
		id = buffer->at(0);
		buffer->clear();
	}
	else {
		if (bytesTransferred != 2) {
			printf("Connection failed. No valid client ID provided by server.\n");
		}
		else {
			printf("Initial read failed, %s (%d)\n", errorCode.message(), errorCode.value());
		}

	}
}


void Client::retrieveIdFromServer() {
	asio::async_read(socket, asio::buffer((char*)&buffer->front(), 2), boost::bind(&Client::initialReadHandler, shared_from_this(), _1, _2));
	asioService.run();
}