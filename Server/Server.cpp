#include "Server.h"

const char Server::ADDRESS[] = "localhost";
const int Server::PORT = 8080;

Server::Server(asio::io_service &asioService) :
asioService(asioService),
acceptor(asioService, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), Server::PORT)),
socket(asioService),
nextId(0) {
}


void Server::startTCP() {
	printf("Server (TCP) started.\n");
	acceptor.listen();
	acceptor.async_accept(socket, boost::bind(&Server::acceptHandler, shared_from_this(), _1));
	asioService.run();
}


void Server::readHandler(const asio::error_code &errorCode, std::size_t bytesTransferred) {
	if (!errorCode) {
		printf("Read successful. Bytes transferred: %d\n", bytesTransferred);
	}
	else if (errorCode == asio::error::eof) {
		printf("Client disconnected\n%d current connections\n", nextId);
	}
	else {
		printf("Read failed! %s (%d)\n", errorCode.message().c_str(), errorCode.value());
	}
}


void Server::writeHandler(const asio::error_code &errorCode, std::size_t bytesTransferred) {
	if (!errorCode) {
		printf("Write successful. Bytes transferred: %d\n", bytesTransferred);
	}
	else if (errorCode == asio::error::eof || errorCode == asio::error::connection_aborted || errorCode == asio::error::connection_reset) {
		printf("Disconnect detected!\n");
	}
	else {
		printf("Write failed! %s (%d)\n", errorCode.message().c_str(), errorCode.value());
	}
	buffer->clear();
}


void Server::acceptHandler(const asio::error_code &errorCode) {
	if (!errorCode) {
		socketMap.emplace(nextId, std::move(socket));
		socket = asio::ip::tcp::socket(asioService);
		assignAndSendClientId();
		printf("Connection made\n%d current connections\n", nextId);
		acceptor.listen();
		acceptor.async_accept(socket, boost::bind(&Server::acceptHandler, shared_from_this(), _1));
	}
	else {
		printf("Accept failed! %s (%d)\n", errorCode.message().c_str(), errorCode.value());
	}
}


void Server::assignAndSendClientId() {
	buffer->push_back(nextId);
	asio::async_write(socketMap.at(nextId), asio::buffer((char*)&buffer->front(), 2), boost::bind(&Server::writeHandler, shared_from_this(), _1, _2));
	++nextId;
}