#include "Player.h"

Player::Player(sf::Vector2f coordinates, float size, std::string nickname) :
	controller(Controller())
{
	player_nickname_font.loadFromFile("Inconsolata_Condensed-Bold.ttf");

	player_circle = new sf::CircleShape(size);
	player_circle->setFillColor(sf::Color::Green);

	player_nickname = sf::Text(nickname, player_nickname_font);
	setNickname(nickname);

	dX = 0; dY = 0;
}

Player::~Player() {
	delete player_circle;
}

sf::Vector2f Player::getCoordinates() {
	return coordinates;
}

void Player::setCoordinates(float x, float y) {
	coordinates = sf::Vector2f(x, y);
	player_circle->setPosition(coordinates);
	player_nickname.setPosition(coordinates);
	player_nickname.setPosition(player_circle->getGlobalBounds().width / 2 - player_nickname.getGlobalBounds().width / 2 + coordinates.x,
								player_circle->getGlobalBounds().height / 2 - player_nickname.getGlobalBounds().height / 2 + coordinates.y);
}

void Player::setCoordinates(sf::Vector2f coordinates) {
	this->coordinates = coordinates;
	player_circle->setPosition(coordinates);
	player_nickname.setPosition(coordinates);
	player_nickname.setPosition(player_circle->getGlobalBounds().width / 2 - player_nickname.getGlobalBounds().width / 2 + coordinates.x,
								player_circle->getGlobalBounds().height / 2 - player_nickname.getGlobalBounds().height / 2 + coordinates.y);

}

std::string Player::getNickname() {
	return nickname;
}

void Player::setNickname(std::string nickname) {
	this->nickname = nickname;
	player_nickname.setCharacterSize(50);
	player_nickname.setFillColor(sf::Color::Black);
	player_nickname.setPosition(player_circle->getGlobalBounds().width / 2 - player_nickname.getGlobalBounds().width / 2,
								player_circle->getGlobalBounds().height / 2 - player_nickname.getGlobalBounds().height / 2);
}

float Player::getdX() const{
	return dX;
}

float Player::getdY() const {
	return dY;
}

void Player::update(sf::Event& event, float delta_time) {
	controller.update(event, this, delta_time);

}

void Player::draw(sf::RenderTarget& window, sf::RenderStates states) const {
	window.draw(*player_circle);
	window.draw(player_nickname);
}