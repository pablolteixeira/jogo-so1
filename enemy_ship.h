#ifndef enemy_ship_h
#define enemy_ship_h

#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Vector2.hpp>
#include "enums/direction.h"
#include "player_ship.h"

class EnemyShip {
public:
    EnemyShip(sf::Vector2f position, Direction direction, PlayerShip* player);
    ~EnemyShip();
    sf::Sprite sprite;
    void update(float dt);
    void render(sf::RenderWindow& window);
	void die();

	bool isAlive;
    
private:
    sf::Vector2f direction;
    float speed;
    float shootDelay;
    float shootTimer;
    sf::Texture texture;
	PlayerShip *player;
    //Shot shot; // Assumption: Shot class for the shots fired by the enemy
    
    void move(float dt);
    void shoot();
	void updateDirection();

	sf::Clock deathClock;
};

#endif
