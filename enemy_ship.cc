#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include "enemy_ship.h"

EnemyShip::EnemyShip(sf::Vector2f position, Direction direction) {
    // Load the texture, set initial direction, speed, etc.
    if (!texture.loadFromFile("sprites/space_ships/enemy_space_ship1.png")) {
        exit(1);
    }

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

void EnemyShip::update(float dt) {
    // Move the enemy ship
    this->move(dt);

    // Increase the shootTimer
    shootTimer += dt;

    // If shootTimer > shootDelay, reset timer and shoot
    if (shootTimer > shootDelay) {
        shootTimer = 0.f;
        this->shoot();
    }
}

void EnemyShip::move(float dt) {
    sprite.move(direction * speed * dt);
}

void EnemyShip::shoot() {
    // Create a new shot and add to the shot list
    // You can set the shot direction to player's position at the moment of shooting
}

void EnemyShip::render(sf::RenderWindow& window) {
    window.draw(this->sprite);
}

