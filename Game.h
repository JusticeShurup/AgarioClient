#ifndef _GAME_H_
#define _GAME_H_
#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "Server.h"


class Game
{
public:
	Game(int window_width, int window_heigth, std::string server_address);
	~Game();

	void initWindow(int window_width, int window_heigth);
	void initMainPlayer();

	Player* getMainPlayer();

	Player* getPlayerByNickname(std::string);

	void addPlayer(Player* player);
	void removePlayer(std::string player_nickname);
	void run();
	
	void update();
	void render();

private:
	sf::Vector2i window_size;
	sf::RenderWindow *window;
	sf::Event event;
	sf::Clock clock;

	Server server;
	std::map<std::string, Player*> players;

	float delta_time;

	Player *main_player;

	bool is_running;
};
#endif
