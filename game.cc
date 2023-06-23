#include "game.h"
#include "game_object.h"
#include <vector>

bool Game::checkCollision(GameObject& obj1, GameObject& obj2) {
	return obj1.getSprite().getGlobalBounds().
		intersects(obj2.getSprite().getGlobalBounds());
}

// TODO: game::run()
void Game::run() {

}


