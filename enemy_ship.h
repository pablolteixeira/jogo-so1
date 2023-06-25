#ifndef enemy_ship_h
#define enemy_ship_h

#include "enums/algorithm.h"
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
class Game;

#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Vector2.hpp>
#include "enums/direction.h"
#include "player_ship.h"

class EnemyShip {
public:
    EnemyShip(sf::Vector2f position, Direction direction, PlayerShip* player, Algorithm algo);
    ~EnemyShip();
    sf::Sprite sprite;
    void update(float dt, Game& game, sf::Vector2u window_size, int velocity);
    void render(sf::RenderWindow& window);
	void die();

	bool isAlive = true;
    
	sf::FloatRect getBoundaryRectangle(const sf::Vector2f& newPosition);
    
private:
	Direction direction;
    sf::Vector2f directionVector;
	float init_speed = 60.f;
	float speed;
	float shootDelay = 2.f;
    float shootTimer = 0.f;
	float shootSpeed = 260.f;
    sf::Texture texture;
	PlayerShip *player;
	Algorithm algo;
	sf::Clock randomMoveClock;  
    sf::Vector2f randomDirection;  

    void move(float dt, sf::RectangleShape left_frame);
    void shoot();
	void updateDirection();
	void updateSprite();

	sf::Clock deathClock;
};

#endif
