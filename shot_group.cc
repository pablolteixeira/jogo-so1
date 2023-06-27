#include "shot.h"
#include "shot_group.h"
#include "thread/traits.h"
#include <memory>
#include <vector>
#include "window.h"

__BEGIN_API

std::vector<std::unique_ptr<Shot>> ShotGroup::shots = {};

void ShotGroup::addShot(std::unique_ptr<Shot> shot) {
	shots.push_back(std::move(shot));
}

void ShotGroup::runShots() {
	// FIXME: while game is running
	while (true) {
		if (!window->isPaused) {
			for (auto& shot : shots) {
				shot->update(dt);	
			}
		}
		Thread::yield();
	}
};

void ShotGroup::setWindow(Window* window) {
	this->window = window;
}

__END_API
