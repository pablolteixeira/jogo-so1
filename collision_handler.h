#ifndef collision_handler_h
#define collision_handler_h

class Game;

#include "player_ship.h"
#include "enemy_ship.h"

class CollisionHandler {
public:
    CollisionHandler(Game& game);

	void checkPlayerEnemyCollision(PlayerShip& player, EnemyShip& enemy);
<<<<<<< HEAD
	void checkShotBorderCollision(Shot& shot);
=======
	void checkEnemyEnemyCollision(EnemyShip& en1, EnemyShip& en2);
	//void checkShotBorderCollision(Shot& shot);
>>>>>>> 004d195 (I don't remmeber what i did here)
	void checkShipBorderCollision(EnemyShip& ship);
	void checkShipBorderCollision(PlayerShip& ship);
	void checkShotShipCollision(Shot& shot, PlayerShip& ship);
	void checkShotShipCollision(Shot& shot, EnemyShip& ship);

    // Other necessary functions and members for collision handling
private:
	Game& game;
};

#endif
