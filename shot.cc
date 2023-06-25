#include "shot.h"

Shot::Shot(float startX, float startY, Direction direction) {
    position.x = startX;
    position.y = startY;
    direction = direction;

    texture.loadFromFile("sprites/space_ships/shot.png");
    sprite.setTexture(texture);
    sprite.setPosition(position.x, position.y);
}

Shot::~Shot() {

}

void Shot::update() {
    switch (direction)
    {
    case Direction::UP:
        position.y -= 20.0f;
        break;
    case Direction::DOWN:
        position.y += 20.0f;
        break;
    case Direction::RIGHT:
        position.x += 20.0f;
        break;
    case Direction::LEFT:
        position.x -= 20.0f;
        break;
    default:
        break;
    }
}