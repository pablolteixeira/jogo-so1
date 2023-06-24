
#ifndef enemy_spaceship_h
#define enemy_spaceship_h

#include "game_object.h"
#include "spaceship.h"
#include <SFML/Graphics.hpp>

class EnemySpaceship : public Spaceship {
public:
    EnemySpaceship();
    void move() override;
};

#endif
