#include "shot.h"
#include "enums/ship_type.h"
#include <iostream>

Shot::Shot(float startX, float startY, Direction direction, ShipType shipType) {
    this->position.x = startX;
    this->position.y = startY;
    this->direction = direction;
    this->shipType = shipType;

    this->texture.loadFromFile("sprites/space_ships/shot.png");
    this->sprite.setTexture(this->texture);
    this->sprite.scale(0.5f, 0.5f);
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

void Shot::updateShots() {
	for (auto& shot : Shot::_shots) {
		shot->update();
	}
}

void Shot::renderShots(sf::RenderWindow& window) {
	for (auto& shot : Shot::_shots) {
		shot->render(window);
	}
}