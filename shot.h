#ifndef SHOT_H
#define SHOT_H

#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include "enums/direction.h"
#include "enums/ship_type.h"
#include "thread/traits.h"

__BEGIN_API

class Shot {
public:
    Shot(float startX, float startY, Direction direction, ShipType shipType, float speed);
    ~Shot();
	void die();
    void update(float dt);
    
    sf::Sprite sprite;
    bool isDead;
    ShipType ship_type;

private:
	void move(float dt);

    //  Variables
    sf::Vector2f position;
    sf::Texture texture;
    float speed;
    Direction direction;
	sf::Vector2f directionVector;
};

__END_API

#endif

