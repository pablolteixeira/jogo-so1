#include "collision_handler.h"
#include "enemy_ship.h"
#include "enums/ship_type.h"
#include "player_ship.h"
#include "game.h"
#include <vector>
#include <iostream>

CollisionHandler::CollisionHandler(Game& game) : game(game) {
}

void CollisionHandler::checkPlayerEnemyCollision(PlayerShip& player, EnemyShip& enemy) {
	if (enemy.isAlive && enemy.sprite.getGlobalBounds().intersects(player.sprite.getGlobalBounds())) {
		enemy.die();
		player.lives--;
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

void CollisionHandler::checkShotShipCollision(Shot& shot, PlayerShip& ship) {
	if (shot.sprite.getGlobalBounds().intersects(ship.sprite.getGlobalBounds()) &&
			shot.ship_type != ShipType::PLAYER) {
		shot.die();
		ship.lives--;
	}
}

void CollisionHandler::checkShotShipCollision(Shot& shot, EnemyShip& ship) {
	if (shot.sprite.getGlobalBounds().intersects(ship.sprite.getGlobalBounds()) &&
			shot.ship_type != ShipType::ENEMY &&
			ship.isAlive) { 
		std::cout << "shoulda died fr\n";
		shot.die();
		ship.die();
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

