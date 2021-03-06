#include "Player.h"

Player::Player(sf::Vector2i coordinates, float size, std::string nickname) :
	controller(Controller())
{
	player_nickname_font.loadFromFile("Inconsolata_Condensed-Bold.ttf");

	this->size = size;
	player_circle = new sf::CircleShape(size);
	player_circle->setFillColor(sf::Color::Green);

	player_nickname = sf::Text(nickname, player_nickname_font);
	setNickname(nickname);

}

Player::~Player() {
	delete player_circle;
}

sf::Vector2i Player::getCoordinates() const{
	return coordinates;
}

void Player::setCoordinates(int x, int y) {
	coordinates = sf::Vector2i(x, y);
	player_circle->setPosition(sf::Vector2f(coordinates));
	player_nickname.setPosition(sf::Vector2f(coordinates));
	player_nickname.setPosition(player_circle->getGlobalBounds().width / 2 - player_nickname.getGlobalBounds().width / 2 + coordinates.x,
								player_circle->getGlobalBounds().height / 2 - player_nickname.getGlobalBounds().height / 2 + coordinates.y - 10);
}

void Player::setCoordinates(sf::Vector2i coordinates) {
	this->coordinates = coordinates;
	player_circle->setPosition(sf::Vector2f(coordinates));
	player_nickname.setPosition(sf::Vector2f(coordinates));
	player_nickname.setPosition(player_circle->getGlobalBounds().width / 2 - player_nickname.getGlobalBounds().width / 2 + coordinates.x,
								player_circle->getGlobalBounds().height / 2 - player_nickname.getGlobalBounds().height / 2 + coordinates.y - 10);

}

std::string Player::getNickname() {
	return nickname;
}

void Player::setNickname(std::string nickname) {
	this->nickname = nickname;
	player_nickname.setString(nickname);
	player_nickname.setCharacterSize(50);
	player_nickname.setFillColor(sf::Color::Black);
	player_nickname.setPosition(player_circle->getGlobalBounds().width / 2 - player_nickname.getGlobalBounds().width / 2,
								player_circle->getGlobalBounds().height / 2 - player_nickname.getGlobalBounds().height / 2);
}

void Player::update(sf::Event& event, float delta_time) {
	controller.update(event, this, delta_time);

}

void Player::draw(sf::RenderTarget& window, sf::RenderStates states) const {
	window.draw(*player_circle);
	window.draw(player_nickname);
}