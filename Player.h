//#include <Poco/Net/DatagramSocket.h>
#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "Controller.h"

class Player : public sf::Drawable
{

public:
	static const int MAX_PLAYER_NICKNAME_SIZE = 10;
	
	Player(sf::Vector2i coordinates, float size, std::string nickname);
	~Player();

	sf::Vector2i getCoordinates() const;
	void setCoordinates(int x, int y);
	void setCoordinates(sf::Vector2i coordinates);

	std::string getNickname();
	void setNickname(std::string nickname);

	
	void update(sf::Event& event, float delta_time);
	virtual void draw(sf::RenderTarget& window, sf::RenderStates states) const;


private:
	friend class Controller;
	sf::Vector2i coordinates;
	float size;
	std::string nickname;

	Controller controller;

	sf::CircleShape *player_circle;
	sf::Font player_nickname_font;
	sf::Text player_nickname;

};

