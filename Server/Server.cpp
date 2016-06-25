#include "Server.h"

const char Server::ADDRESS[] = "localhost";
const int Server::PORT = 8080;

Server::Server(asio::io_service &asioService) :
asioService(asioService),
acceptor(asioService, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), Server::PORT)),
socket(asioService),
nextId(-1),
readBuffer(new std::vector<uint16_t>(1)),
writeBuffer(new std::vector<uint16_t>(1)) {
}


void Server::startTCP() {
	printf("Server (TCP) started.\n");
	acceptor.listen();
	acceptor.async_accept(socket, boost::bind(&Server::acceptHandler, shared_from_this(), _1));
	SDL_CreateThread(&sdlAsioServiceWrapper, "ServerAsioServiceThread", &asioService);
	game.startUpdateLoop();
}


void Server::readHandler(const asio::error_code &errorCode, std::size_t bytesTransferred, int clientId) {
	if (!errorCode) {
		//printf("Read successful. %d bytes transferred from client %d\n", bytesTransferred, clientId);
		readBuffer->clear();
		asio::async_read(socketMap.at(clientId), asio::buffer((char*)&readBuffer->front(), 2), boost::bind(&Server::readHandler, shared_from_this(), _1, _2, clientId));
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
		//printf("Write successful. %d bytes transferred to client %d\n", bytesTransferred, clientId);
		writeBuffer->clear();
		writeBuffer->push_back(clientId);
		asio::async_write(socketMap.at(clientId), asio::buffer((char*)&writeBuffer->front(), 2), boost::bind(&Server::writeHandler, shared_from_this(), _1, _2, clientId));
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
	writeBuffer->at(0) = nextId;
	asio::async_write(socketMap.at(nextId), asio::buffer((char*)&writeBuffer->front(), 2), boost::bind(&Server::writeHandler, shared_from_this(), _1, _2, nextId));
}


static int sdlAsioServiceWrapper(void* param) {
	((asio::io_service*) param)->run();
	return 0;
}