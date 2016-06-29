#include "Server.h"

const char Server::ADDRESS[] = "localhost";
const int Server::PORT = 8080;

Server::Server(asio::io_service &asioService) :
asioService(asioService),
acceptor(asioService, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), Server::PORT)),
socket(asioService),
nextId(-1),
readBuffer(new Packet) {
}


void Server::startTCP() {
	printf("Server (TCP) started.\n");
	acceptor.listen();
	acceptor.async_accept(socket, boost::bind(&Server::acceptHandler, shared_from_this(), _1));
	boost::thread asioServiceThread(boost::bind(&asio::io_service::run, &asioService));
	game.startUpdateLoop();
}


void Server::readHandler(const asio::error_code &errorCode, std::size_t bytesTransferred) {
	uint8_t clientId = readBuffer->getClientId();

	// potential speed up: multi thread handling process so we can call async_read right away. just make a copy of the readBuffer to do the processing
	if (!errorCode) {
		asio::async_read(socketMap.at(clientId), readBuffer->toAsioBuffer(), boost::bind(&Server::readHandler, shared_from_this(), _1, _2));
	}
	else if (errorCode == asio::error::eof) {
		socketMap.erase(clientId);
		printf("Client %d disconnected\n%d current connections\n", clientId, socketMap.size());
	}
	else {
		printf("Read failed! %s (%d)\n", errorCode.message().c_str(), errorCode.value());
	}
}


void Server::writeHandler(const asio::error_code &errorCode, std::size_t bytesTransferred, int clientId) {
	if (!errorCode) {
		Packet packet;
		asio::async_write(socketMap.at(clientId), packet.toAsioBuffer(), boost::bind(&Server::writeHandler, shared_from_this(), _1, _2, clientId));
	}
	else if (errorCode == asio::error::eof || errorCode == asio::error::connection_aborted || errorCode == asio::error::connection_reset) {
		socketMap.erase(clientId);
		printf("Client %d disconnected\n%d current connections\n", clientId, socketMap.size());
	}
	else {
		printf("Write failed! %s (%d)\n", errorCode.message().c_str(), errorCode.value());
	}
}


void Server::acceptHandler(const asio::error_code &errorCode) {
	if (!errorCode) {
		++nextId;
		socketMap.emplace(nextId, std::move(socket));
		socket = asio::ip::tcp::socket(asioService);
		assignAndSendClientId();
		printf("Connection made\n%d current connections\n", socketMap.size());
		acceptor.listen();
		acceptor.async_accept(socket, boost::bind(&Server::acceptHandler, shared_from_this(), _1));
	}
	else {
		printf("Accept failed! %s (%d)\n", errorCode.message().c_str(), errorCode.value());
	}
}


void Server::assignAndSendClientId() {
	Packet packet;
	packet.setClientId(nextId);
	packet.setXPosition(100);
	asio::async_write(socketMap.at(nextId), packet.toAsioBuffer(), boost::bind(&Server::writeHandler, shared_from_this(), _1, _2, nextId));
}