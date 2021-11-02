#include "Game.h"
#include <iostream>
Game::Game(int width, int heigth) :
	is_running(true), 
	server("127.0.0.1:1337")
{
	initWindow(width, heigth);
	initMainPlayer();
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
	main_player = new Player(sf::Vector2f(100, 100), 100, "Huy");
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
	updateNet();
	main_player->setCoordinates(server.getCoordinates());
}

void Game::updateNet() {
	float data[2] = { main_player->getdX(), main_player->getdY() };
	server.sendDeltaCoordinates(data);
}

void Game::render() {
	window->clear();
	window->draw(*main_player);
	window->display();
}