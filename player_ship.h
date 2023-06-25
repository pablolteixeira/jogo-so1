#ifndef player_ship_h
#define player_ship_h

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>
#include "enums/direction.h"
#include "input.h"
#include "enums/shared_state.h"

class PlayerShip {
public:
    PlayerShip(sf::Vector2f position, Direction shipDirection, SharedState& state, Input& input);
    ~PlayerShip();
    void update();
    void render(sf::RenderWindow& window);
    sf::Sprite sprite;
	//void run();
    
private:
    float speed;
    float shootDelay;
    float shootTimer;
    sf::Vector2f position;
    sf::Texture texture;
	Input& input;
	SharedState& shared_state;
	std::vector<sf::Texture> textures;
	//Input keyboard_input;
    //Shot shot; // Assumption: Shot class for the shots fired by the enemy
    
	void getUserInput();
    void move(float x, float y);
    void shoot();
};

#endif
