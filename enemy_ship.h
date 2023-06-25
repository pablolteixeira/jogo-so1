#ifndef enemy_ship_h
#define enemy_ship_h

#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include "enums/direction.h"

class EnemyShip {
public:
    EnemyShip(sf::Vector2f position, Direction direction);
    ~EnemyShip();
    sf::Sprite sprite;
    void update(float dt);
    void render(sf::RenderWindow& window);
    
private:
    sf::Vector2f direction;
    float speed;
    float shootDelay;
    float shootTimer;
    sf::Texture texture;
    //Shot shot; // Assumption: Shot class for the shots fired by the enemy
    
    void move(float dt);
    void shoot();
};

#endif
