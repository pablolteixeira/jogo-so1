#include "collision_handler.h"
#include "enemy_ship.h"
#include "enums/ship_type.h"
#include "player_ship.h"
#include "game.h"
#include <vector>
#include <math.h>
#include <iostream>

CollisionHandler::CollisionHandler(Game& game) : game(game) {
}

void CollisionHandler::checkPlayerEnemyCollision(PlayerShip& player, EnemyShip& enemy) {
	if (enemy.isAlive && enemy.sprite.getGlobalBounds().intersects(player.sprite.getGlobalBounds())) {
		enemy.die();
		game.updateVelocityCounter();
		player.lives--;
	}
}

void CollisionHandler::checkEnemyEnemyCollision(EnemyShip& en1, EnemyShip& en2) {
    if (en1.isAlive && en2.isAlive && en1.sprite.getGlobalBounds().intersects(en2.sprite.getGlobalBounds())) {
        // Calculate the move direction for each enemy
        sf::Vector2f moveDirection1 = en1.sprite.getPosition() - en2.sprite.getPosition();
        sf::Vector2f moveDirection2 = -moveDirection1;

        // Normalize the move direction
        float length1 = std::sqrt(moveDirection1.x * moveDirection1.x + moveDirection1.y * moveDirection1.y);
        if (length1 != 0) {
            moveDirection1.x /= length1;
            moveDirection1.y /= length1;
        }

        float length2 = std::sqrt(moveDirection2.x * moveDirection2.x + moveDirection2.y * moveDirection2.y);
        if (length2 != 0) {
            moveDirection2.x /= length2;
            moveDirection2.y /= length2;
        }

        // Move the enemies apart
        en1.sprite.move(moveDirection1);
        en2.sprite.move(moveDirection2);
    }
}

void CollisionHandler::checkShipBorderCollision(PlayerShip& ship) {
	sf::FloatRect shipBounds = ship.sprite.getGlobalBounds();
	sf::FloatRect frameBounds = game.left_frame.getGlobalBounds();

	// Check if the ship has hit the left frame boundary
    if (shipBounds.left < frameBounds.left) {
        ship.sprite.setPosition(frameBounds.left + 5, ship.sprite.getPosition().y);
    }
	
    // Check if the ship has hit the top frame boundary
    if (shipBounds.top < frameBounds.top) {
        ship.sprite.setPosition(ship.sprite.getPosition().x, frameBounds.top + 5);
    }
	
    // Check if the ship has hit the right frame boundary
    if (shipBounds.left + shipBounds.width > frameBounds.left + frameBounds.width) {
        ship.sprite.setPosition(frameBounds.left + frameBounds.width - shipBounds.width - 5, ship.sprite.getPosition().y);
    }
	
    // Check if the ship has hit the bottom frame boundary
    if (shipBounds.top + shipBounds.height > frameBounds.top + frameBounds.height) {
        ship.sprite.setPosition(ship.sprite.getPosition().x, frameBounds.top + frameBounds.height - shipBounds.height - 5);
    }
}

void CollisionHandler::checkShipBorderCollision(EnemyShip& ship) {
	sf::FloatRect shipBounds = ship.sprite.getGlobalBounds();
	sf::FloatRect frameBounds = game.left_frame.getGlobalBounds();

	// Check if the ship has hit the left frame boundary
    if (shipBounds.left < frameBounds.left) {
        ship.sprite.setPosition(frameBounds.left, ship.sprite.getPosition().y);
    }
	
    // Check if the ship has hit the top frame boundary
    if (shipBounds.top < frameBounds.top) {
        ship.sprite.setPosition(ship.sprite.getPosition().x, frameBounds.top);
    }
	
    // Check if the ship has hit the right frame boundary
    if (shipBounds.left + shipBounds.width > frameBounds.left + frameBounds.width) {
        ship.sprite.setPosition(frameBounds.left + frameBounds.width - shipBounds.width, ship.sprite.getPosition().y);
    }
	
    // Check if the ship has hit the bottom frame boundary
    if (shipBounds.top + shipBounds.height > frameBounds.top + frameBounds.height) {
        ship.sprite.setPosition(ship.sprite.getPosition().x, frameBounds.top + frameBounds.height - shipBounds.height);
    }
}

void CollisionHandler::checkShotShipCollision(Shot& shot, PlayerShip& ship) {
	if (shot.sprite.getGlobalBounds().intersects(ship.sprite.getGlobalBounds()) &&
			shot.ship_type != ShipType::PLAYER) {
		shot.die();
		ship.lives--;
	}
}

void CollisionHandler::checkShotShotCollision(Shot& shot1, Shot& shot2) {
	if (shot1.sprite.getGlobalBounds().intersects(
				shot2.sprite.getGlobalBounds())) {
		shot1.die();
		shot2.die();
	}
}

void CollisionHandler::checkShotShipCollision(Shot& shot, PlayerShip& playerShip, EnemyShip& enemyShip) {
	if (shot.sprite.getGlobalBounds().intersects(enemyShip.sprite.getGlobalBounds()) &&
			shot.ship_type == ShipType::PLAYER &&
			enemyShip.isAlive && !shot.isDead) { 		
		enemyShip.die();
        shot.die();
		game.updateVelocityCounter();

        playerShip.increaseScore();
	}
}

void CollisionHandler::checkShotBorderCollision(Shot& shot) {
	for (auto it = Shot::_shots.begin(); it != Shot::_shots.end();) {
		sf::FloatRect shotBounds = (*it)->sprite.getGlobalBounds();
		sf::FloatRect frameBounds = game.left_frame.getGlobalBounds();

        // Check if the shot has hit any frame boundary
        if (shotBounds.left < frameBounds.left ||
            shotBounds.top < frameBounds.top ||
            shotBounds.left + shotBounds.width > frameBounds.left + frameBounds.width ||
            shotBounds.top + shotBounds.height > frameBounds.top + frameBounds.height) {
            it = Shot::_shots.erase(it);
        } else {
            ++it;
        }
    }
}

