#include "Game.h"
#include <fstream>

int main() {
	std::ifstream f("ServerAddress.txt");
	std::string server_address;
	f >> server_address;
	Game agario(1920, 1080, server_address);
	agario.run();
	return 0;
}