
#include "collision_handler.h"
#include "enemy_spaceship.h"
#include "game_object.h"
#include <SFML/Graphics.hpp>
#include "../game.h"

bool CollisionHandler::checkCollisions() {
	printf("COLLISION\n");
}

void CollisionHandler::handleShotEnemyHit(Shot *shot, EnemySpaceship *ship) {
	shot->die();
	ship->die();
	Game::player_ship->increaseScore(100);
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
