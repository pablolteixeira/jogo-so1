#ifndef shot_group_h
#define shot_group_h

#include "shot.h"
#include "thread/traits.h"
#include <memory>
#include <vector>

__BEGIN_API

class ShotGroup {
public:
	static void runShots();
	void addShot(std::unique_ptr<Shot> shot) {
        shots.push_back(std::move(shot));
    }

private:
	std::vector<std::unique_ptr<Shot>> shots;
};

__END_API

#endif
