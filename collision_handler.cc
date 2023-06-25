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
		std::cout << frameBounds.left << std::endl;
        std::cout << "Ship collided with the left frame boundary\n";
        // Adjust the ship's position to not cross the left frame boundary
        ship.sprite.setPosition(frameBounds.left + 5, ship.sprite.getPosition().y);
    }
	
    // Check if the ship has hit the top frame boundary
    if (shipBounds.top < frameBounds.top) {
		std::cout << frameBounds.top << std::endl;
        std::cout << "Ship collided with the top frame boundary\n";
        // Adjust the ship's position to not cross the top frame boundary
        ship.sprite.setPosition(ship.sprite.getPosition().x, frameBounds.top + 5);
    }
	
    // Check if the ship has hit the right frame boundary
    if (shipBounds.left + shipBounds.width > frameBounds.left + frameBounds.width) {
		std::cout << frameBounds.left + frameBounds.width << std::endl;
        std::cout << "Ship collided with the right frame boundary\n";
        // Adjust the ship's position to not cross the right frame boundary
        ship.sprite.setPosition(frameBounds.left + frameBounds.width - shipBounds.width - 5, ship.sprite.getPosition().y);
    }
	
    // Check if the ship has hit the bottom frame boundary
    if (shipBounds.top + shipBounds.height > frameBounds.top + frameBounds.height) {
		std::cout << frameBounds.top + frameBounds.height << std::endl;
        std::cout << "Ship collided with the bottom frame boundary\n";
        // Adjust the ship's position to not cross the bottom frame boundary
        ship.sprite.setPosition(ship.sprite.getPosition().x, frameBounds.top + frameBounds.height - shipBounds.height - 5);
    }
}

void CollisionHandler::checkShipBorderCollision(EnemyShip& ship) {
	sf::FloatRect shipBounds = ship.sprite.getGlobalBounds();
	sf::FloatRect frameBounds = game.left_frame.getGlobalBounds();

	// Check if the ship has hit the left frame boundary
    if (shipBounds.left < frameBounds.left) {
		std::cout << frameBounds.left << std::endl;
        std::cout << "Ship collided with the left frame boundary\n";
        // Adjust the ship's position to not cross the left frame boundary
        ship.sprite.setPosition(frameBounds.left + 5, ship.sprite.getPosition().y);
    }
	
    // Check if the ship has hit the top frame boundary
    if (shipBounds.top < frameBounds.top) {
		std::cout << frameBounds.top << std::endl;
        std::cout << "Ship collided with the top frame boundary\n";
        // Adjust the ship's position to not cross the top frame boundary
        ship.sprite.setPosition(ship.sprite.getPosition().x, frameBounds.top + 5);
    }
	
    // Check if the ship has hit the right frame boundary
    if (shipBounds.left + shipBounds.width > frameBounds.left + frameBounds.width) {
		std::cout << frameBounds.left + frameBounds.width << std::endl;
        std::cout << "Ship collided with the right frame boundary\n";
        // Adjust the ship's position to not cross the right frame boundary
        ship.sprite.setPosition(frameBounds.left + frameBounds.width - shipBounds.width - 5, ship.sprite.getPosition().y);
    }
	
    // Check if the ship has hit the bottom frame boundary
    if (shipBounds.top + shipBounds.height > frameBounds.top + frameBounds.height) {
		std::cout << frameBounds.top + frameBounds.height << std::endl;
        std::cout << "Ship collided with the bottom frame boundary\n";
        // Adjust the ship's position to not cross the bottom frame boundary
        ship.sprite.setPosition(ship.sprite.getPosition().x, frameBounds.top + frameBounds.height - shipBounds.height - 5);
    }
}

//void CollisionHandler::checkPlayerEnemyCollision(PlayerShip& player, EnemyShip& enemy) {
//	
//}
