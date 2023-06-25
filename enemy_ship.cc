#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include "enemy_ship.h"
#include "player_ship.h"
#include <math.h>

EnemyShip::EnemyShip(sf::Vector2f position, Direction direction, PlayerShip* player) {
    // Load the texture, set initial direction, speed, etc.
    if (!texture.loadFromFile("sprites/space_ships/enemy_space_ship1.png")) {
        exit(1);
    }

	this->player = player;

	switch (direction) {
		case Direction::UP:
    		this->direction = sf::Vector2f(0.f, -1.f); 
			texture.loadFromFile("sprites/space_ships/enemy_space_ship1.png");
			break;
		case Direction::DOWN:
			this->direction = sf::Vector2f(0.f, 1.f);
			texture.loadFromFile("sprites/space_ships/enemy_space_ship3.png");
			break;
		case Direction::LEFT:
			this->direction = sf::Vector2f(-1.f, 0.f);
			texture.loadFromFile("sprites/space_ships/enemy_space_ship2.png");
			break;
		case Direction::RIGHT:
			this->direction = sf::Vector2f(1.f, 0.f);
			texture.loadFromFile("sprites/space_ships/enemy_space_ship4.png");
			break;
	}

    sprite.setTexture(texture);
    sprite.setScale(0.5, 0.5);
	sprite.setPosition(position);
    
    speed = 100.f; // Arbitrary speed value
    shootDelay = 2.f; // Fire every 2 seconds
    shootTimer = 0.f;
}

EnemyShip::~EnemyShip(){

}

void EnemyShip::die() {
	isAlive = false;
	deathClock.restart();
}

void EnemyShip::update(float dt) {
 	if (!isAlive && deathClock.getElapsedTime().asSeconds() >= 2.f) {
        isAlive = true;
    }

    if (isAlive) {
        // If the ship is alive, update its position and shoot
        this->move(dt);
        shootTimer += dt;
        if (shootTimer > shootDelay) {
            shootTimer = 0.f;
            this->shoot();
        }
    }
}

void EnemyShip::move(float dt) {
	sf::Vector2f playerPosition = player->getPosition();
    sf::Vector2f currentPosition = sprite.getPosition();
    sf::Vector2f directionToPlayer = playerPosition - currentPosition;

    // Normalize the direction
    float magnitude = sqrt((directionToPlayer.x * directionToPlayer.x) + (directionToPlayer.y * directionToPlayer.y));
    direction = sf::Vector2f(directionToPlayer.x / magnitude, directionToPlayer.y / magnitude);

    // Update the sprite direction
    updateDirection();

    sprite.move(direction * speed * dt);
}

void EnemyShip::updateDirection() {
    // Determine the angle of the direction vector
    float angle = atan2(direction.y, direction.x) * 180 / 3.14159;

    if (angle > -45 && angle <= 45) {
        // Right
        this->direction = sf::Vector2f(1.f, 0.f);
        texture.loadFromFile("sprites/space_ships/enemy_space_ship4.png");
    } else if (angle > 45 && angle <= 135) {
        // Down
        this->direction = sf::Vector2f(0.f, 1.f);
        texture.loadFromFile("sprites/space_ships/enemy_space_ship3.png");
    } else if ((angle > 135 && angle <= 180) || (angle >= -180 && angle <= -135)) {
        // Left
        this->direction = sf::Vector2f(-1.f, 0.f);
        texture.loadFromFile("sprites/space_ships/enemy_space_ship2.png");
    } else if (angle > -135 && angle <= -45) {
        // Up
        this->direction = sf::Vector2f(0.f, -1.f); 
        texture.loadFromFile("sprites/space_ships/enemy_space_ship1.png");
    }
    
    sprite.setTexture(texture);
}
void EnemyShip::shoot() {
    // Create a new shot and add to the shot list
    // You can set the shot direction to player's position at the moment of shooting
}

void EnemyShip::render(sf::RenderWindow& window) {
    if (isAlive) {
        window.draw(this->sprite);
    }
}

