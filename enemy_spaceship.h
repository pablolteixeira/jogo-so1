
#ifndef enemy_spaceship_h
#define enemy_spaceship_h

#include "game_object.h"
#include <SFML/Graphics.hpp>

class EnemySpaceship : public GameObject {
public:
    EnemySpaceship();
    void move();
    void fire();
};

#endif
