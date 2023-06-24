#ifndef player_spaceship_h
#define player_spaceship_h

#include "game_object.h"
#include "spaceship.h"
#include <SFML/Graphics.hpp>

class PlayerSpaceship : public Spaceship {
public:
	PlayerSpaceship();
    void handleInput(sf::Event event);
	void increaseScore(int score);
	bool isDead() { return lives <= 0; }

	int score = 0;
	int lives = 3;
};

#endif
