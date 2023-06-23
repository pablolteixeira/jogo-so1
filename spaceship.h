#ifndef spaceship_h
#define spaceship_h

#include "game_object.h"
#include <SFML/Graphics.hpp>

class Spaceship : public GameObject {
public:
	int position_x;
	int position_y;
	int width;
   	int height;

	Spaceship();
    void handleInput(sf::Event event);
    void fire();
};

#endif
