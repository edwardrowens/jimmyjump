#include "Server.h"

const char Server::ADDRESS[] = "localhost";
const int Server::PORT = 8080;

Server::Server(asio::io_service asioService) :
asioService(asioService) {
}


Server::~Server() {
}


void Server::startTCP() {
	asio::ip::tcp::acceptor acceptor(asioService, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), Server::PORT));
	std::cout << "Server ready" << std::endl;
}