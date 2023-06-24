
#include "shot.h"
#include "../game.h"
#include "game_object.h"
#include <SFML/Graphics.hpp>
#include <tuple>

std::tuple<bool, GameObject*> Shot::detectHit() {
	for (GameObject * obj : Game::getGameObjects()) {
		if (Game::checkCollision(*this, *obj)) {
			return std::make_tuple(true, obj);
		}
	}
	return std::make_tuple(false, nullptr);
}

void Shot::run() {
	while (Game::isRunning()) {
		if (isAlive) {
			move();
			if (auto [collision, obj_hit] = detectHit(); collision) {
				obj_hit->die(); // TODO: prob override die for every object
				die();
			}
		}
    }
}

//void Shot::die() {
//	isAlive = false;
//	queue_mutex.p();
//	active_shots.erase(std::remove(active_shots.begin(), active_shots.end(), this), active_shots.end());
//	queue_mutex.v();
//}
