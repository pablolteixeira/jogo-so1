#include "collision_handler.h"
#include "enemy_ship.h"
#include "player_ship.h"
#include "game.h"
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

void CollisionHandler::checkShotBorderCollision(Shot& shot) {
    sf::FloatRect shotBounds = shot.sprite.getGlobalBounds();
	sf::FloatRect frameBounds = game.left_frame.getGlobalBounds();

    // Check if the ship has hit the left frame boundary
    if (shotBounds.left < frameBounds.left) {
        delete shot;
    }
	
    // Check if the ship has hit the top frame boundary
    if (shotBounds.top < frameBounds.top) {
        delete shot;
    }
	
    // Check if the ship has hit the right frame boundary
    if (shotBounds.left + shotBounds.width > frameBounds.left + frameBounds.width) {
        delete shot;
    }
	
    // Check if the ship has hit the bottom frame boundary
    if (shotBounds.top + shotBounds.height > frameBounds.top + frameBounds.height) {
        delete shot;
    }
}

