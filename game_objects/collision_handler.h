#ifndef collision_handler
#define collision_handler

#include "game_object.h"
#include <SFML/Graphics.hpp>
#include "shot.h"
#include "enemy_spaceship.h"
#include "player_spaceship.h"

class CollisionHandler {
public:
	CollisionHandler();
	bool checkCollision(GameObject *obj1, GameObject *obj2);
	void handlePlayerHit(PlayerSpaceship *player_ship, GameObject *hitter);
	void handleShotEnemyHit(Shot *shot, EnemySpaceship *ship);
	void handleBorderShotCollision(Shot *shot);
	void handleBorderShipCollision(Spaceship *ship);
};

#endif 
