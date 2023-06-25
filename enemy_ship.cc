#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include "collision_handler.h"
#include "enemy_ship.h"
#include "enums/direction.h"
#include "player_ship.h"
#include <iostream>
#include <math.h>
#include "game.h"
#include "shot.h"

EnemyShip::EnemyShip(sf::Vector2f position, Direction direction, PlayerShip* player) {
    // Load the texture, set initial direction, speed, etc.
    if (!texture.loadFromFile("sprites/space_ships/enemy_space_ship1.png")) {
        exit(1);
    }

	this->player = player;

	switch (direction) {
		case Direction::UP:
    		this->directionVector = sf::Vector2f(0.f, -1.f); 
			texture.loadFromFile("sprites/space_ships/enemy_space_ship1.png");
			break;
		case Direction::DOWN:
			this->directionVector = sf::Vector2f(0.f, 1.f);
			texture.loadFromFile("sprites/space_ships/enemy_space_ship3.png");
			break;
		case Direction::LEFT:
			this->directionVector = sf::Vector2f(-1.f, 0.f);
			texture.loadFromFile("sprites/space_ships/enemy_space_ship2.png");
			break;
		case Direction::RIGHT:
			this->directionVector = sf::Vector2f(1.f, 0.f);
			texture.loadFromFile("sprites/space_ships/enemy_space_ship4.png");
			break;
	}

	this->direction = direction;

    sprite.setTexture(texture);
    sprite.setScale(0.5, 0.5);
	sprite.setPosition(position);
    
    speed = 85.f; // Arbitrary speed value
    shootDelay = 2.f; // Fire every 2 seconds
    shootTimer = 0.f;
}

EnemyShip::~EnemyShip(){

}

void EnemyShip::die() {
	shootTimer = 0.f;
	isAlive = false;
	deathClock.restart();
}

sf::FloatRect EnemyShip::getBoundaryRectangle(const sf::Vector2f& newPosition) {
    float offset_x = texture.getSize().x * sprite.getScale().x / 2.f;
    float offset_y = texture.getSize().y * sprite.getScale().y / 2.f;

    sf::Vector2f centeredPosition(newPosition.x - offset_x, newPosition.y - offset_y);

	return sf::FloatRect(centeredPosition, sf::Vector2f(texture.getSize().x * sprite.getScale().x, texture.getSize().y * sprite.getScale().y));
}

void EnemyShip::update(float dt, Game& game) {
	if (!isAlive) {
        if (deathClock.getElapsedTime().asSeconds() >= 2.f) {
            sf::FloatRect frameBounds = game.left_frame.getGlobalBounds();
            sf::FloatRect playerBounds = player->sprite.getGlobalBounds();

            float minDistanceFromBorders = 50.f;
            float minDistanceFromPlayer = 250.f;

            sf::Vector2f newPosition;
            bool validPosition = false;

            while (!validPosition) {
                newPosition.x = frameBounds.left + minDistanceFromBorders + static_cast<float>(rand() % static_cast<int>(frameBounds.width - 2 * minDistanceFromBorders));
                newPosition.y = frameBounds.top + minDistanceFromBorders + static_cast<float>(rand() % static_cast<int>(frameBounds.height - 2 * minDistanceFromBorders));

                sf::Vector2f playerPosition = player->getPosition();
                float distanceFromPlayer = std::sqrt(std::pow(playerPosition.x - newPosition.x, 2) + std::pow(playerPosition.y - newPosition.y, 2));
                if (distanceFromPlayer >= minDistanceFromPlayer) {
                    validPosition = true;

                    // Check if the position overlaps with another enemy ship
                    for (const auto& enemy : game.enemies) {
                        sf::FloatRect enemyBounds = enemy->sprite.getGlobalBounds();
                        sf::FloatRect newBounds = this->getBoundaryRectangle(newPosition);
                        if (enemyBounds.intersects(newBounds)) {
                            validPosition = false;
                            break;
                        }
                    }
                }
            }

            sprite.setPosition(newPosition);
            isAlive = true;
        }
    } else {  
        this->move(dt);
        shootTimer += dt;
        if (shootTimer > shootDelay) {
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
    directionVector = sf::Vector2f(directionToPlayer.x / magnitude, directionToPlayer.y / magnitude);

    updateDirection();
    sprite.move(directionVector * speed * dt);
}

void EnemyShip::updateDirection() {
    float angle = atan2(directionVector.y, directionVector.x) * 180 / 3.14159;

    if (angle > -45 && angle <= 45) {
        // Right
		direction = Direction::RIGHT;
        this->directionVector = sf::Vector2f(1.f, 0.f);
        texture.loadFromFile("sprites/space_ships/enemy_space_ship4.png");
    } else if (angle > 45 && angle <= 135) {
        // Down
		direction = Direction::DOWN;
        this->directionVector = sf::Vector2f(0.f, 1.f);
        texture.loadFromFile("sprites/space_ships/enemy_space_ship3.png");
    } else if ((angle > 135 && angle <= 180) || (angle >= -180 && angle <= -135)) {
        // Left
		direction = Direction::LEFT;
        this->directionVector = sf::Vector2f(-1.f, 0.f);
        texture.loadFromFile("sprites/space_ships/enemy_space_ship2.png");
    } else if (angle > -135 && angle <= -45) {
        // Up
		direction = Direction::UP;
        this->directionVector = sf::Vector2f(0.f, -1.f); 
        texture.loadFromFile("sprites/space_ships/enemy_space_ship1.png");
    }
    
    sprite.setTexture(texture);
}

void EnemyShip::shoot() {
	if (!isAlive || shootTimer < shootDelay) {
		return;
	}

    float shotWidth = sprite.getGlobalBounds().width / 3.0f;
    float shotHeight = sprite.getGlobalBounds().height / 3.0f;

    float playerCenterX = sprite.getPosition().x + sprite.getGlobalBounds().width / 2.0f;
    float playerCenterY = sprite.getPosition().y + sprite.getGlobalBounds().height / 2.0f;

    float shotStartX = playerCenterX - shotWidth / 2.0f;
    float shotStartY = playerCenterY - shotHeight / 2.0f;

    Shot* shot = new Shot(shotStartX, shotStartY, this->direction, ShipType::ENEMY, shootSpeed);
    Shot::_shots.push_back(shot);

	shootTimer = 0.f;
}

void EnemyShip::render(sf::RenderWindow& window) {
    if (isAlive) {
        window.draw(this->sprite);
    }
}

