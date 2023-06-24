#ifndef spaceship_h
#define spaceship_h

#include "game_object.h"
#include <SFML/Graphics.hpp>
#include "direction.h"

class Spaceship : public GameObject {
public:
	int position_x;
	int position_y;
	int width;
   	int height;
	Direction direction = Direction::BACKWARDS;

	Spaceship();
    void fire();
	virtual void move();
};

#endif
