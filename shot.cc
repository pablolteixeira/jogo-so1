#include "shot.h"
#include <iostream>

Shot::Shot(float startX, float startY, Direction direction) {
    this->position.x = startX;
    this->position.y = startY;
    this->direction = direction;

    this->texture.loadFromFile("sprites/space_ships/shot.png");
    this->sprite.setTexture(this->texture);
    this->sprite.setPosition(this->position);
}

Shot::~Shot() {

}

void Shot::update() {
    switch (direction)
    {
    case Direction::UP:
        this->position.y -= 20.0f;
        break;
    case Direction::DOWN:
        this->position.y += 20.0f;
        break;
    case Direction::RIGHT:
        this->position.x += 20.0f;
        break;
    case Direction::LEFT:
        this->position.x -= 20.0f;
        break;
    default:
        break;
    }

    this->sprite.setPosition(this->position);
}

void Shot::render(sf::RenderWindow& window) {
    window.draw(this->sprite);
}