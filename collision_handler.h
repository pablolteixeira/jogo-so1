#ifndef collision_handler_h
#define collision_handler_h

#include "player_ship.h"
#include "enemy_ship.h"
#include "thread/traits.h"

__BEGIN_API

class Window;

class CollisionHandler {
public:
	CollisionHandler() {};

	void setWindow(Window* window) { this->window = window; };
	void checkCollisions();
	void run();

	void checkPlayerEnemyCollision();
	void checkShotBorderCollision();
	void checkEnemyEnemyCollision();
	void checkShipBorderCollision();
	void checkShotShipCollision();
	void checkShotShotCollision();

private:
	Window* window;
};

__END_API

#endif
