#ifndef shot_group_h
#define shot_group_h

#include "shot.h"
#include "thread/traits.h"
#include <memory>
#include <vector>
#include "thread/thread.h"

__BEGIN_API

const float dt = 1.0f / 60.0f;

class ShotGroup {
public:
	ShotGroup(){};
	~ShotGroup(){
		// TODO: delete shots maybe?
	};

	static void runShots();

	void addShot(std::unique_ptr<Shot> shot);	

	static std::vector<std::unique_ptr<Shot>> shots;
};

__END_API

#endif
