#ifndef enemy_ship_h
#define enemy_ship_h

<<<<<<< HEAD
#include "enums/algorithm.h"
=======
#include "enums/movement_algorithm.h"
>>>>>>> 004d195 (I don't remmeber what i did here)
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
<<<<<<< HEAD
    EnemyShip(sf::Vector2f position, Direction direction, PlayerShip* player, Algorithm algo);
=======
    EnemyShip(sf::Vector2f position, Direction direction, PlayerShip* player, MovementAlgorithm algorithm);
>>>>>>> 004d195 (I don't remmeber what i did here)
    ~EnemyShip();
    sf::Sprite sprite;
    void update(float dt, Game& game, sf::Vector2u window_size);
    void render(sf::RenderWindow& window);
	void die();

	bool isAlive = true;
    
private:
	Direction direction;
    sf::Vector2f directionVector;
    float speed;
    float shootDelay = 2.f;
    float shootTimer = 0.f;
	float shootSpeed = 260.f;
    sf::Texture texture;
	PlayerShip *player;
<<<<<<< HEAD

	Algorithm algo;
	sf::Clock randomMoveClock;  
    sf::Vector2f randomDirection;  
    
    void move(float dt, sf::RectangleShape left_frame);
=======
    
    void move(float dt, sf::Vector2u window_size);
>>>>>>> 004d195 (I don't remmeber what i did here)
    void shoot();
	void updateDirection();
	void updateSprite();

<<<<<<< HEAD
	sf::FloatRect getBoundaryRectangle(const sf::Vector2f& newPosition);
=======
	MovementAlgorithm algorithm; 
	sf::Clock moveClock;
	sf::Vector2f randomDirection;
>>>>>>> 004d195 (I don't remmeber what i did here)
	sf::Clock deathClock;
};

#endif
