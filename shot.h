#ifndef SHOT_H
#define SHOT_H

#include <SFML/Graphics.hpp>
#include "enums/direction.h"


class Shot {
public:
    Shot(float startX, float startY, Direction direction);
    ~Shot();
    void update();

private:
    //  Variables

    sf::Vector2f position;
    sf::Texture texture;
    sf::Sprite sprite;
    float speed;
    Direction direction;
};

#endif