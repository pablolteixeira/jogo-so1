#include "shot.h"
#include "shot_group.h"
#include "thread/traits.h"
#include <memory>
#include <vector>

__BEGIN_API

std::vector<std::unique_ptr<Shot>> ShotGroup::shots = {};

void ShotGroup::addShot(std::unique_ptr<Shot> shot) {
	shots.push_back(std::move(shot));
}

void ShotGroup::runShots() {
	// FIXME: while game is running
	while (true) {
		for (auto& shot : shots) {
			shot->update(dt);	
		}
		Thread::yield();
	}
};

__END_API
