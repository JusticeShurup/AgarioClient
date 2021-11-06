#include "Game.h"
#include <iostream>
#include <fstream>
#include "Server.h"


Game::Game(int width, int heigth, std::string server_address) :
	is_running(true), 
	server(server_address)
{
	initWindow(width, heigth);
	initMainPlayer();
	server.setGame(this);
	server.run();
}

Game::~Game(){
	delete window;
	delete main_player;
}

void Game::initWindow(int width, int heigth) {
	window_size = sf::Vector2i(width, heigth);
	sf::ContextSettings settings;
	settings.antialiasingLevel = 50;
	window = new sf::RenderWindow(sf::VideoMode(window_size.x, window_size.y), "Agar.io", sf::Style::Default, settings);
}

void Game::initMainPlayer() {
	std::cout << "Enter Player name: ";
	std::string nickname;
	std::cin >> nickname;
	main_player = new Player(sf::Vector2i(100, 100), 100, nickname);
}

Player* Game::getMainPlayer(){
	return main_player;
}

Player* Game::getPlayerByNickname(std::string nickname) {
	return players[nickname];
}

void Game::addPlayer(Player* player) {
	players.insert(std::pair<std::string, Player*>(player->getNickname(), player));
}

void Game::removePlayer(std::string nickname) {
	players.erase(nickname);
}

void Game::run() {
	while (is_running) {
		update();
		render();
	}
}

void Game::update() {
	delta_time = clock.restart().asSeconds();

	while (window->pollEvent(event)) {
		if (event.type == sf::Event::Closed) {
			is_running = false;
			window->close();
		}
	}

	main_player->update(event, delta_time);
	server.setCoordinates(main_player->getCoordinates().x, main_player->getCoordinates().y);
	main_player->setCoordinates(server.getCoordinates());
}

void Game::render() {
	window->clear();
	window->draw(*main_player);
	for (auto i = players.begin(); i != players.end(); i++) {
		window->draw(*i->second);
	}
	window->display();
}