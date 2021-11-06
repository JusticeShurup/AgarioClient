#include "Controller.h"
#include "Player.h"


Controller::Controller(){}

Controller::~Controller() {}

void Controller::update(sf::Event &event, Player *player, float delta_time) {
	int x = player->getCoordinates().x; 
	int y = player->getCoordinates().y;
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		player->setCoordinates(x, y - 1);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		player->setCoordinates(x, y + 1);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		player->setCoordinates(x - 1, y);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		player->setCoordinates(x + 1, y);
	}
}