#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Vector2.hpp>
#include "enemy_ship.h"
#include "enums/algorithm.h"
#include "enums/direction.h"
#include "player_ship.h"
#include <iostream>
#include <math.h>
#include <ostream>
#include "shot.h"
#include "thread/traits.h"
#include "window.h" 

__BEGIN_API

EnemyShip::EnemyShip(sf::Vector2f position, Direction direction, Algorithm algo) {
	if (!texture.loadFromFile("sprites/space_ships/enemy_space_ship1.png")) {
        exit(1);
    }

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
	this->algo = algo;

	if (algo == Algorithm::SNIPER) {
		directionVector = sf::Vector2f(-1.f, 0.f);
	}

	isAlive = true;

    sprite.setTexture(texture);
    sprite.setScale(0.43, 0.43);
	sprite.setPosition(position);
    
    speed = init_speed; // Arbitrary speed value
    shootDelay = 2.f; // Fire every 2 seconds
    shootTimer = 0.f;
}

EnemyShip::~EnemyShip(){

}

void EnemyShip::run() {
	// FIXME: remove while true
	const float dt = 1.0f / 60.0f;
	while (window->getIsRunning()) {
		if (window == nullptr) {
			Thread::yield();
		}
		if (!window->isPaused || !window->getIsStopped()) {
			update(dt);
		}
		Thread::yield();
	}
}

void EnemyShip::die() {
	shootTimer = 0.f;
	isAlive = false;
	deathClock.restart();
}

void EnemyShip::update(float dt) {
	speed = init_speed + (window->getGameVelocity()*1.25f)*15.f;

	if (!isAlive) {
		if (deathClock.getElapsedTime().asSeconds() >= 2.f) {
			if (algo == Algorithm::SNIPER) {
				sf::Vector2f respawnPosition;
				Direction respawnDirection;

				do {
					respawnPosition.x = std::rand() % int(window->left_frame.getSize().x);
					bool isUpperQuadrant = (std::rand() % 2 == 0);
					respawnPosition.y = isUpperQuadrant 
						? std::rand() % int(window->left_frame.getSize().y / 4) 
						: window->left_frame.getSize().y - (std::rand() % int(window->left_frame.getSize().y / 4));

					respawnDirection = isUpperQuadrant ? Direction::DOWN : Direction::UP;
				} while (!isSafeRespawnPosition(respawnPosition, 50.f, 100.f));

				sprite.setPosition(respawnPosition);
				direction = respawnDirection; // Update direction
				updateDirectionVector(); 
				isAlive = true;
			} else if (algo == Algorithm::FOLLOW_PLAYER) {
				sf::Vector2f respawnPosition;
				do {
					respawnPosition.x = std::rand() % int(window->left_frame.getSize().x);
					respawnPosition.y = std::rand() % int(window->left_frame.getSize().y);
				} while (!isSafeRespawnPosition(respawnPosition, 50.f, 250.f));
				sprite.setPosition(respawnPosition);
				isAlive = true;
			}
			deathClock.restart();
		}
	} else {
		this->move(dt);
		shootTimer += dt;
		if (shootTimer > shootDelay) {
			this->shoot();
		}
	}
}

bool EnemyShip::isSafeRespawnPosition(const sf::Vector2f& position, float minDistanceToShip, float minDistanceToPlayer) {
    // Check distance to player
    sf::Vector2f playerPosition = window->getPlayerPosition();
    float distanceToPlayer = std::sqrt(std::pow(position.x - playerPosition.x, 2) 
                            + std::pow(position.y - playerPosition.y, 2));
    if (distanceToPlayer < minDistanceToPlayer) {
        return false;
    }

    // Check distance to other enemy ships
    for (auto& enemy : window->enemies) {
        if (enemy.get() != this) { // Do not check against self
            sf::Vector2f enemyPosition = enemy->sprite.getPosition();
            float distanceToEnemy = std::sqrt(std::pow(position.x - enemyPosition.x, 2) 
                            + std::pow(position.y - enemyPosition.y, 2));
            if (distanceToEnemy < minDistanceToShip) {
                return false;
            }
        }
    }

    return true;
}

sf::FloatRect EnemyShip::getBoundaryRectangle(const sf::Vector2f& newPosition) {
    float offset_x = texture.getSize().x * sprite.getScale().x / 2.f;
    float offset_y = texture.getSize().y * sprite.getScale().y / 2.f;

    sf::Vector2f centeredPosition(newPosition.x - offset_x, newPosition.y - offset_y);

	return sf::FloatRect(centeredPosition, sf::Vector2f(texture.getSize().x * sprite.getScale().x, texture.getSize().y * sprite.getScale().y));
}

void EnemyShip::move(float dt) {
	if (!isAlive) {
		return;
	}

	switch (algo) {
		case Algorithm::FOLLOW_PLAYER:
			{
				sf::Vector2f playerPosition = window->getPlayerPosition();
				sf::Vector2f currentPosition = sprite.getPosition();
				sf::Vector2f directionToPlayer = playerPosition - currentPosition;

                // Normalize the direction
                float magnitude = sqrt((directionToPlayer.x * directionToPlayer.x) + (directionToPlayer.y * directionToPlayer.y));
                directionVector = sf::Vector2f(directionToPlayer.x / magnitude, directionToPlayer.y / magnitude);

                updateDirection();
                sprite.move(directionVector * speed * dt);
                break;
            }
		case Algorithm::SNIPER:
            {
				sf::FloatRect shipBounds = sprite.getGlobalBounds();
				sf::FloatRect frameBounds = window->left_frame.getGlobalBounds();

				directionVector.y = 0.f;
                
                if (randomMoveClock.getElapsedTime().asSeconds() == 0.f) {
                    directionVector.x = (static_cast<float>(rand()) / RAND_MAX) > 0.5f ? 1.f : -1.f;
                }

                if (shipBounds.left <= frameBounds.left) {
					std::cout << "check left\n"; 
                    directionVector.x = 1.f;  // Move to the right
                    randomMoveClock.restart();
                }
                else if (shipBounds.left + shipBounds.width >= frameBounds.left + frameBounds.width) {
					std::cout << "check right\n"; 
                    directionVector.x = -1.f;  // Move to the left
                    randomMoveClock.restart();
                }
                else if (randomMoveClock.getElapsedTime().asSeconds() >= 2.f) {
					std::cout << ">= 2f\n"; 
					directionVector.x = (rand() % 2 == 0) ? 1.0f : -1.0f;
                    randomMoveClock.restart();
                }

				float middleOfLeftFrame = window->left_frame.getSize().y / 2.0f;
				if (sprite.getPosition().y < middleOfLeftFrame) {
					direction = Direction::DOWN;
				} else {
					direction = Direction::UP;
				}
				updateSprite();
				
                sprite.move(directionVector * speed * dt);
                break;
            }
    }
}

void EnemyShip::updateSprite() {
	switch (direction) {
		case Direction::DOWN:
        	texture.loadFromFile("sprites/space_ships/enemy_space_ship3.png");
			break;
		case Direction::RIGHT:
			texture.loadFromFile("sprites/space_ships/enemy_space_ship4.png");
			break;
		case Direction::LEFT:
        	texture.loadFromFile("sprites/space_ships/enemy_space_ship2.png");
			break;
		case Direction::UP:
        	texture.loadFromFile("sprites/space_ships/enemy_space_ship1.png");
			break;
	}	
}

void EnemyShip::updateDirectionVector() {
    switch(direction) {
        case Direction::UP:
            directionVector = sf::Vector2f(0, -1);
            break;
        case Direction::DOWN:
            directionVector = sf::Vector2f(0, 1);
            break;
        case Direction::LEFT:
            directionVector = sf::Vector2f(-1, 0);
            break;
        case Direction::RIGHT:
            directionVector = sf::Vector2f(1, 0);
            break;
        default:
            // Handle other cases or throw an exception
            break;
    }
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

	std::unique_ptr<Shot> shot = std::make_unique<Shot>(shotStartX, shotStartY, this->direction, ShipType::ENEMY, 320.f);
	window->addShot(std::move(shot));
	shootTimer = 0.f;
}

__END_API
