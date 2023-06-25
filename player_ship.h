#ifndef player_ship_h
#define player_ship_h

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>
#include "enums/direction.h"
#include "input.h"
#include "enums/shared_state.h"
#include "shot.h"

class PlayerShip {
public:
    PlayerShip(sf::Vector2f position, Direction shipDirection, SharedState& state, Input& input);
    ~PlayerShip();
    void update(float dt);
    void updateShots();
    void render(sf::RenderWindow& window);
    void renderShots(sf::RenderWindow& window);
    void increaseScore();
	void getUserInput(sf::Keyboard::Key key);
	sf::Vector2f getPosition() { return sprite.getPosition(); };	
    sf::Sprite sprite;
	int lives = 3;
	int score = 0;
    
private:
    float speed = 75.f;
    float shootDelay;
    float shootTimer;
    Direction direction;
	sf::Vector2f directionVector;
    sf::Texture texture;
	Input& input;
	SharedState& shared_state;
	std::vector<sf::Texture> textures;
    std::vector<Shot*> playerShots;
	//Input keyboard_input;
    //Shot shot; // Assumption: Shot class for the shots fired by the enemy
    
    void move(float dt);
    void shoot();
	void changeDirection(Direction direction);
};

#endif
