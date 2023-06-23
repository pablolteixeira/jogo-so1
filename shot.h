#ifndef shot_h
#define shot_h

#include "game_object.h"
#include "traits.h"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include "semaphore.h"

class Shot : public GameObject {
public:
    Shot(int pos_x, int pos_y) { position_x = pos_x; position_y = pos_y; };
	int position_x;
	int position_y;
	bool isAlive = true;
	void run(); 
	static std::vector<Shot> getActiveShots() { return active_shots; } ;
	static SOLUTION::Semaphore queue_mutex; 
	void die() override;
   
private:
	void move();
	std::tuple<bool, GameObject*> detectHit();
	std::vector<Shot> shots;
	static std::vector<Shot> active_shots;
};

#endif
