#include "Server.h"
#include <iostream>

Server::Server(std::string server_addr) :
	address(server_addr),
	coordinates(sf::Vector2f(0, 0)),
	adapter(*this, &Server::receiveCoordinates)
{
	last_server_seq = 0; 
	seq = 1;
	is_running = false;
	flag = false;
}

Server::~Server(){}

void Server::run() {
	is_running = true;
	thread.start(adapter);
}

void Server::close() {
	is_running = false;
	while(!flag) {}
	thread.join();
}

void Server::sendDeltaCoordinates(float deltaCoordinates[2]) {
	float data[3] = { int(seq), deltaCoordinates[0], deltaCoordinates[1] };
	socket.sendTo(data, sizeof(float) * 3, address);
	seq++;
}

void Server::receiveCoordinates() {
	while (is_running) {
		flag = false;
		float data[3]; // {seq, dX, dY};
		std::cout << "here" << std::endl;
		socket.receiveFrom(data, sizeof(float) * 3, address);
		std::cout << data[0] << std::endl;
		if (last_server_seq < data[0]) {
			last_server_seq = int(data[0]);
			coordinates.x = data[1];
			coordinates.y = data[2];
			std::cout << data[1] << " " << data[2] << std::endl;
		}
		flag = true;
	}
}

sf::Vector2f Server::getCoordinates() {
	return coordinates;
}