#include "Client.h"

Client::Client(asio::io_service& asioService) :
asioService(asioService),
socket(asioService),
resolver(asioService),
readBuffer(new std::vector<uint16_t>(1)),
writeBuffer(new std::vector<uint16_t>()),
id(-1) {
}


void Client::connectToServer(std::string address, std::string port) {
	endpoint = resolver.resolve(asio::ip::tcp::resolver::query(address, port));
	asio::async_connect(socket, endpoint, boost::bind(&Client::connectHandler, shared_from_this(), _1, _2));
	asioService.run();
	asio::error_code shutdownAttempt;
	socket.shutdown(asio::ip::tcp::socket::shutdown_both, shutdownAttempt);
	if (shutdownAttempt) {
		printf("shut down error: %s (%d)\n", shutdownAttempt.message().c_str(), shutdownAttempt.value());
	}
	socket.close();
}


void Client::connectHandler(asio::error_code errorCode, asio::ip::tcp::resolver::iterator resolverIter) {
	if (!errorCode) {
		printf("Client connected successfully\n");
		asio::async_read(socket, asio::buffer((char*)&readBuffer->front(), 2), boost::bind(&Client::initialReadHandler, shared_from_this(), _1, _2));
	}
	else {
		printf("Client connection failed! %s (%d)\n", errorCode.message().c_str(), errorCode.value());
	}
}


void Client::readHandler(asio::error_code errorCode, std::size_t bytesTransferred) {
	if (!errorCode) {
		readBuffer->clear();
		asio::async_read(socket, asio::buffer((char*)&readBuffer->front(), 2), boost::bind(&Client::readHandler, shared_from_this(), _1, _2));
	}
	else {
		printf("Read failed, %s (%d)\n", errorCode.message().c_str(), errorCode.value());
	}
}


void Client::initialReadHandler(asio::error_code errorCode, std::size_t bytesTransferred) {
	if (!errorCode) {
		id = readBuffer->at(0);
		readBuffer->clear();
		asio::async_read(socket, asio::buffer((char*)&readBuffer->front(), 2), boost::bind(&Client::readHandler, shared_from_this(), _1, _2));
	}
	else {
		printf("Read failed, %s (%d)\n", errorCode.message().c_str(), errorCode.value());
	}
}


void Client::writeHandler(asio::error_code errorCode, std::size_t bytesTransferred) {
	if (!errorCode) {
		writeBuffer->clear();
		writeBuffer->push_back(id);
		asio::async_write(socket, asio::buffer((char*)&writeBuffer->front(), 2), boost::bind(&Client::readHandler, shared_from_this(), _1, _2));
	}
	else {
		printf("Read failed, %s (%d)\n", errorCode.message().c_str(), errorCode.value());
	}
}