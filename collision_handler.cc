#include "collision_handler.h"
#include "enemy_ship.h"
#include "enums/ship_type.h"
#include "player_ship.h"
#include "game.h"
#include "thread/traits.h"
#include <vector>
#include <math.h>
#include <iostream>
#include "window.h"

__BEGIN_API

void CollisionHandler::run() {
	while (window->getIsRunning()) {
		if (window == nullptr) {
			Thread::yield();
		}
		checkCollisions();
		Thread::yield();
	}
}

void CollisionHandler::checkCollisions() {
	// FIXME: shot going twice
	checkPlayerEnemyCollision();
	checkEnemyEnemyCollision();
	checkShotBorderCollision();
	checkShipBorderCollision();
	checkShotShipCollision();
	checkShotShotCollision();
}

void CollisionHandler::checkPlayerEnemyCollision() {
	for (auto& enemy : window->enemies) {
		if (enemy->isAlive && enemy->sprite.getGlobalBounds().intersects(window->getPlayerBounds())) {
			enemy->die();
			window->increasePlayerScore();
			window->updateVelocityCounter();
			window->lowerPlayerLives();
		}
	}
}

void CollisionHandler::checkEnemyEnemyCollision() {
	for (auto& en1 : window->enemies) {
		for (auto& en2 : window->enemies) {
			if (en1 != en2 && en1->isAlive && en2->isAlive &&
					en1->sprite.getGlobalBounds().intersects(
						en2->sprite.getGlobalBounds())) {
				// Calculate the move direction for each enemy
				sf::Vector2f moveDirection1 = en1->sprite.getPosition() - en2->sprite.getPosition();
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
				en1->sprite.move(moveDirection1);
				en2->sprite.move(moveDirection2);
			}
		}
	}
}

void CollisionHandler::checkShotBorderCollision() {
	for (auto it = window->shot_group->shots.begin(); it != window->shot_group->shots.end();) {
		sf::FloatRect shotBounds = (*it)->sprite.getGlobalBounds();
		sf::FloatRect frameBounds = window->left_frame.getGlobalBounds();

        // Check if the shot has hit any frame boundary
        if (shotBounds.left < frameBounds.left ||
            shotBounds.top < frameBounds.top ||
            shotBounds.left + shotBounds.width > frameBounds.left + frameBounds.width ||
            shotBounds.top + shotBounds.height > frameBounds.top + frameBounds.height) {
            it = window->shot_group->shots.erase(it);
			std::cout<<"deletedshot!\n";
        } else {
            ++it;
        }
    }
}

void CollisionHandler::checkShipBorderCollision() {
	sf::FloatRect shipBounds = window->getPlayerBounds();
	sf::FloatRect frameBounds = window->left_frame.getGlobalBounds();
    if (shipBounds.left < frameBounds.left) {
        window->setPlayerPosition(frameBounds.left, window->getPlayerPosition().y);
    }
    if (shipBounds.top < frameBounds.top) {
        window->setPlayerPosition(window->getPlayerPosition().x, frameBounds.top);
    }
    if (shipBounds.left + shipBounds.width > frameBounds.left + frameBounds.width) {
        window->setPlayerPosition(frameBounds.left + frameBounds.width - shipBounds.width, window->getPlayerPosition().y);
    }
    if (shipBounds.top + shipBounds.height > frameBounds.top + frameBounds.height) {
        window->setPlayerPosition(window->getPlayerPosition().x, frameBounds.top + frameBounds.height - shipBounds.height);
    }

	for (auto& enemy : window->enemies) {
		sf::FloatRect shipBounds = enemy->sprite.getGlobalBounds();
		sf::FloatRect frameBounds = window->left_frame.getGlobalBounds();
		if (shipBounds.left < frameBounds.left) {
			enemy->sprite.setPosition(frameBounds.left, enemy->sprite.getPosition().y);
		}
		if (shipBounds.top < frameBounds.top) {
			enemy->sprite.setPosition(enemy->sprite.getPosition().x, frameBounds.top);
		}
		if (shipBounds.left + shipBounds.width > frameBounds.left + frameBounds.width) {
			enemy->sprite.setPosition(frameBounds.left + frameBounds.width - shipBounds.width, enemy->sprite.getPosition().y);
		}
		if (shipBounds.top + shipBounds.height > frameBounds.top + frameBounds.height) {
			enemy->sprite.setPosition(enemy->sprite.getPosition().x, frameBounds.top + frameBounds.height - shipBounds.height);
		}
	}
}

void CollisionHandler::checkShotShipCollision() {
	for (auto it = window->shot_group->shots.begin(); it != window->shot_group->shots.end();) {
		if((*it)->ship_type == ShipType::ENEMY) {
			if ((*it)->sprite.getGlobalBounds().intersects(
						window->getPlayerBounds()))
			{
				it = window->shot_group->shots.erase(it);
				window->updateVelocityCounter();
				window->decreasePlayerLives();
				return;
			}
		} else if ((*it)->ship_type == ShipType::PLAYER) {
			for (auto& enemy : window->enemies) {
				if ((*it)->sprite.getGlobalBounds().intersects(
						enemy->sprite.getGlobalBounds()) &&
						enemy->isAlive)
				{
					enemy->die();
					window->increasePlayerScore();
					it = window->shot_group->shots.erase(it);
					window->updateVelocityCounter();
					// TODO: player increase score
					return;
				}
			}
		} 
		++it;
	}
}

void CollisionHandler::checkShotShotCollision() {
	for (auto it1 = window->shot_group->shots.begin(); it1 != window->shot_group->shots.end();) {
		bool collisionDetected = false;

		for (auto it2 = window->shot_group->shots.begin(); it2 != window->shot_group->shots.end();) {
			if (it1 != it2 && (*it1)->sprite.getGlobalBounds().intersects((*it2)->sprite.getGlobalBounds())) {
				it2 = window->shot_group->shots.erase(it2);
				collisionDetected = true;
				break;
			} else {
				++it2;
			}
		}

		if (collisionDetected) {
			it1 = window->shot_group->shots.erase(it1);
		} else {
			++it1;
		}
	}
}

__END_API

