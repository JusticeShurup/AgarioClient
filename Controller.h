#ifndef _CONTROLLER_H_
#define _CONTROLLER_H_
#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"

class Player;

class Controller
{
public:
	Controller();
	~Controller();

	void update(sf::Event &event, Player *player, float delta_time);
};
#endif
