#ifndef enemy_ship_h
#define enemy_ship_h

#include "enums/algorithm.h"
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Vector2.hpp>
#include "enums/direction.h"
#include "thread/traits.h"
#include <iostream>

__BEGIN_API

class Window;

class EnemyShip {
public:
	EnemyShip(sf::Vector2f position, Direction direction, Algorithm algo);
    ~EnemyShip();
    sf::Sprite sprite;
    void update(float dt);
	void die();
	void run();

	bool isAlive = true;

	void setWindow(Window* window) { this->window = window; } 

private:
	Window *window = nullptr;	

	Direction direction;
    sf::Vector2f directionVector;
	float init_speed = 60.f;
	float speed;
	float shootDelay = 2.f;
    float shootTimer = 0.f;
	float shootSpeed = 260.f;
    sf::Texture texture;
	Algorithm algo;
	sf::Clock randomMoveClock;  
    sf::Vector2f randomDirection;  

    void move(float dt);
    void shoot();
	void updateDirection();
	void updateDirectionVector();
	void updateSprite();
	sf::FloatRect getBoundaryRectangle(const sf::Vector2f& position);
	bool isSafeRespawnPosition(const sf::Vector2f& position, float minDistanceToShip, float minDistanceToPlayer);

	sf::Clock deathClock;
};

__END_API

#endif
