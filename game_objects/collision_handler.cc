
#include "collision_handler.h"
#include "enemy_spaceship.h"
#include "game_object.h"
#include <SFML/Graphics.hpp>
#include "game.h"

bool CollisionHandler::checkCollision(GameObject *obj1, GameObject *obj2) {
	return obj1->sprite.getGlobalBounds()
		.intersects(obj2->sprite.getGlobalBounds());
}

void CollisionHandler::handleShotEnemyHit(Shot *shot, EnemySpaceship *ship) {
	Spaceship *player = shot->owner;
	shot->die();
	ship->die();
	player->increaseScore(100);
}

void CollisionHandler::handlePlayerHit(PlayerSpaceship *player_ship, GameObject* hitter) {
	hitter->die();
	if (--player_ship->lives <= 0) {
		Game::end();
	}
}

void CollisionHandler::handleBorderShotCollision(Shot *shot) {
	shot->die();
}

void CollisionHandler::handleBorderShipCollision(Spaceship *shit) {}
