#ifndef _GAME_H_
#define _GAME_H_
#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "Player.h"
#include "Server.h"

class Game
{
public:
	Game(int window_width, int window_heigth);
	~Game();

	void initWindow(int window_width, int window_heigth);
	void initMainPlayer();

	void run();
	
	void update();
	void updateNet();
	void render();

private:
	sf::Vector2i window_size;
	sf::RenderWindow *window;
	sf::Event event;
	sf::Clock clock;

	Server server;

	float delta_time;

	Player *main_player;

	bool is_running;
};
#endif
