#include "Game.h"

Game::Game(int width, int heigth) :
	is_running(true)
{
	initWindow(width, heigth);
	initMainPlayer();
}

Game::~Game(){
	delete window;
	delete main_player;
}

void Game::initWindow(int width, int heigth) {
	window_size = sf::Vector2i(width, heigth);
	sf::ContextSettings settings;
	settings.antialiasingLevel = 50;
	window = new sf::RenderWindow(sf::VideoMode(window_size.x, window_size.y), "TicTacToe");
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
	delta_time = clock.getElapsedTime().asMicroseconds();
	clock.restart();
	delta_time /= 800;

	while (window->pollEvent(event)) {
		if (event.type == sf::Event::Closed) {
			is_running = false;
			window->close();
		}
	}
	main_player->update(event, delta_time);
}

void Game::render() {
	window->clear();
	window->draw(*main_player);
	window->display();
}