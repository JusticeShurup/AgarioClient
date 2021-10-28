#include "Controller.h"
#include "Player.h"


Controller::Controller(){}

Controller::~Controller() {}

void Controller::update(sf::Event &event, Player *player, float delta_time) {
	float x = player->getCoordinates().x; 
	float y = player->getCoordinates().y;
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		player->setCoordinates(x, y - 0.5 * delta_time);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		player->setCoordinates(x, y + 0.5 * delta_time);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		player->setCoordinates(x - 0.5 * delta_time, y);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		player->setCoordinates(x + 0.5 * delta_time, y);
	}
}