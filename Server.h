#ifndef _SERVER_H_
#define _SERVER_H_
#include "Poco/Net/DatagramSocket.h"
#include "Poco/Net/SocketAddress.h"
#include "Poco/RunnableAdapter.h"
#include "Poco/Thread.h"
#include "SFML/System.hpp"
#include "Player.h"
#include <vector>
#include <map>

class Game;

class Server
{

public: 
	Server();

	Server(std::string server_addr);
	~Server();

	void setGame(Game* game);

	void addPlayer(std::string player_nickname, int x, int y);
	void removePlayer(std::string player_nickname);
	bool findPlayer(std::string player_nickname);
	void run();

	void close();

	void updateNet();

	void setCoordinates(int x, int y);

	sf::Vector2i getCoordinates();

private: 
	static const int MAX_PLAYER_DATAGRAM_SIZE = 23; // 10 - MAX_NICKNAME_SIZE, 4 - seq, 4 - X, 4 - Y 
	
	Game *game;
	std::map<std::string, Player*> players;
	uint8_t players_quantity;

	char buffer[MAX_PLAYER_DATAGRAM_SIZE];
	Poco::Thread thread;
	Poco::RunnableAdapter<Server> adapter;
	
	Poco::Net::DatagramSocket socket;
	Poco::Net::SocketAddress address;

	bool is_running;
	bool flag;

	sf::Vector2i coordinates;
	int seq;
	int last_server_seq;
};
#endif

