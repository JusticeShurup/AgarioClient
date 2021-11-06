#include "Game.h"
#include <iostream>

Server::Server() : adapter(*this, &Server::updateNet) {};

Server::Server(std::string server_addr) :
	address(server_addr),
	coordinates(sf::Vector2i(0, 0)),
	adapter(*this, &Server::updateNet),
	buffer{0}
{
	last_server_seq = 0; 
	seq = 1;
	is_running = false;
	flag = false;
	int data[1] = { 1 };
}

Server::~Server(){}

void Server::setGame(Game* game) {
	this->game = game;
}

void Server::addPlayer(std::string nickname, int x, int y) {
	Player* player = new Player(sf::Vector2i(x, y), 100, nickname);
	players.insert(std::pair<std::string, Player*>(nickname, player));
	game->addPlayer(player);
}

void Server::removePlayer(std::string nickname) {
	players.erase(nickname);
	game->removePlayer(nickname);
}

bool Server::findPlayer(std::string nickname) {
	auto search = players.find(nickname);
	if (search != players.end()) {
		return true;
	}
	else {
		return false;
	}
}

void Server::run() {
	is_running = true;
	int x = 0;
	int y = 0;
	*((uint32_t*)buffer) = seq;
	*((int*)buffer + 1) = x;
	*((int*)buffer + 2) = y;
	strcpy(buffer + sizeof(int) * 3, game->getMainPlayer()->getNickname().c_str());
	socket.sendTo(buffer, 22, address);
	seq++;

	socket.receiveFrom(buffer, 23, address);
	int receive_seq = *((uint32_t*)buffer);
	if (receive_seq > last_server_seq) {
		last_server_seq = receive_seq;
		coordinates.x = *((int*)buffer + 1);
		coordinates.y = *((int*)buffer + 2);
	}


	/*
	socket.receiveFrom(buffer, 23, address);
	x = *((int*)buffer + 1);
	y = *((int*)buffer + 2);
	game->getPlayer()->setCoordinates(x, y);
	game->getPlayer()->setNickname(std::string(buffer+12));
	std::cout << uint32_t(buffer[4]) << " " << x << std::endl;
	*/
	thread.start(adapter);
}

void Server::close() {
	is_running = false;
	while(!flag) {}
	thread.join();
}


void Server::updateNet() {
	int data[3] = {0, 0, 0}; // {seq, x, y}
	int players_quantity = 0;
	int x = 0;
	int y = 0;
	while (is_running) {
		int x = coordinates.x; int y = coordinates.y;
		*((uint32_t*)buffer) = seq;
		*((int*)buffer + 1) = x;
		*((int*)buffer + 2) = y;
		strcpy(buffer + sizeof(int) * 3, game->getMainPlayer()->getNickname().c_str());
		socket.sendTo(buffer, 22, address);
		seq++;
		

		socket.receiveFrom(buffer, 23, address);
		int receive_seq = *((uint32_t*)buffer);
		if (receive_seq > last_server_seq) {
			last_server_seq = receive_seq;
			coordinates.x = *((int*)buffer + 1);
			coordinates.y = *((int*)buffer + 2);
			players_quantity = *((uint8_t*)buffer + 3);

			for (int i = 1; i < players_quantity; i++) {
				socket.receiveFrom(buffer, 22, address);
				x = *((int*)buffer + 1);
				y = *((int*)buffer + 2);
				std::string player_nickname(buffer + 12);
				if (!findPlayer(player_nickname)) {
					addPlayer(player_nickname, x, y);
				}
				game->getPlayerByNickname(player_nickname)->setCoordinates(x, y);
			}
		}
	}
}

void Server::setCoordinates(int x, int y) {
	coordinates = sf::Vector2i(x, y);
}

sf::Vector2i Server::getCoordinates() {
	return coordinates;
}