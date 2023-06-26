#ifndef player_ship_h
#define player_ship_h

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Keyboard.hpp>
#include "enums/direction.h"
#include "input.h"
#include "shot.h"
#include "thread/traits.h"
#include <memory>

__BEGIN_API

class PlayerShip {
public:
    PlayerShip(sf::Vector2f position, Direction shipDirection, Input& input);
    ~PlayerShip();
    void update(float dt);
    void updateShots();
    void render(sf::RenderWindow& window);
    void renderShots(sf::RenderWindow& window);
    void increaseScore();
	void processUserInput();
	void setUserKeyPress(sf::Keyboard::Key key);
	void run();
	sf::Vector2f getPosition() { return sprite.getPosition(); };	
    sf::Sprite sprite;
	int lives = 3;
	int score = 0;
    
private:
	bool running;
    float speed = 75.f;
    float shootDelay;
    float shootTimer;
    Direction direction;
	sf::Vector2f directionVector;
    sf::Texture texture;
	Input& input;
	std::vector<sf::Texture> textures;
    std::vector<Shot*> playerShots;
	sf::Keyboard::Key key = sf::Keyboard::KeyCount; // arbitrary value
    
    void move(float dt);
    void shoot();
	void changeDirection(Direction direction);
};

__END_API

#endif
