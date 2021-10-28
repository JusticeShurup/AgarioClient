//#include <Poco/Net/DatagramSocket.h>
#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "Controller.h"

class Player : public sf::Drawable
{
public:
	Player(sf::Vector2f coordinates, float size, std::string nickname);
	~Player();

	sf::Vector2f getCoordinates();
	void setCoordinates(float x, float y);

	std::string getNickname();
	void setNickname(std::string nickname);

	void update(sf::Event& event, float delta_time);
	virtual void draw(sf::RenderTarget& window, sf::RenderStates states) const;

private:
	sf::Vector2f coordinates;
	float size;
	std::string nickname;

	Controller controller;

	sf::CircleShape *player_circle;
	sf::Font player_nickname_font;
	sf::Text player_nickname;
};

