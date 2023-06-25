#ifndef enemy_ship_h
#define enemy_ship_h

#include <SFML/Graphics/Rect.hpp>
class Game;

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
    void update(float dt, Game& game);
    void render(sf::RenderWindow& window);
	void die();

	bool isAlive = true;
    
private:
	Direction direction;
    sf::Vector2f directionVector;
    float speed;
    float shootDelay = 2.f;
    float shootTimer = 0.f;
	float shootSpeed = 180.f;
    sf::Texture texture;
	PlayerShip *player;
    //Shot shot; // Assumption: Shot class for the shots fired by the enemy
    
    void move(float dt);
    void shoot();
	void updateDirection();
	sf::FloatRect getBoundaryRectangle(const sf::Vector2f& newPosition);

	sf::Clock deathClock;
};

#endif
