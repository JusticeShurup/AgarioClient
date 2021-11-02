#ifndef _SERVER_H_
#define _SERVER_H_
#include "Poco/Net/DatagramSocket.h"
#include "Poco/Net/SocketAddress.h"
#include "Poco/RunnableAdapter.h"
#include "Poco/Thread.h"
#include "SFML/System.hpp"
#include <vector>

class Server
{
public: 
	Server(std::string server_addr);
	~Server();

	void run();

	void close();

	void sendDeltaCoordinates(float deltaCoordinates[2]);
	void receiveCoordinates();

	sf::Vector2f getCoordinates();

private: 
	Poco::Thread thread;
	Poco::RunnableAdapter<Server> adapter;
	
	Poco::Net::DatagramSocket socket;
	Poco::Net::SocketAddress address;

	bool is_running;
	bool flag;

	sf::Vector2f coordinates;
	int seq;
	int last_server_seq;
};
#endif

