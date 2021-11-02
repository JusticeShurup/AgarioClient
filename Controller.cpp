#include "Controller.h"
#include "Player.h"


Controller::Controller(){}

Controller::~Controller() {}

void Controller::update(sf::Event &event, Player *player, float delta_time) {
	float x = player->getCoordinates().x; 
	float y = player->getCoordinates().y;
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		player->dY = -(250.f * delta_time);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		player->dY = 250.f * delta_time;
	}
	else {
		player->dY = 0;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		player->dX = -(250.f * delta_time);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		player->dX = 250.f * delta_time;
	}
	else {
		player->dX = 0;
	}
}