#include "shot.h"
#include "enums/ship_type.h"
#include "player_ship.h"
#include <iostream>
#include <vector>

std::vector<Shot*> Shot::_shots;

Shot::Shot(float startX, float startY, Direction direction, ShipType shipType) {
    this->position.x = startX;
    this->position.y = startY;
    this->direction = direction;
    this->ship_type = shipType;

    this->texture.loadFromFile("sprites/space_ships/shot.png");
    this->sprite.setTexture(this->texture);
    this->sprite.scale(0.5f, 0.5f);
    this->sprite.setPosition(this->position);

	Shot::_shots.push_back(this);
}

Shot::~Shot() {
}

void Shot::move() {
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

void Shot::update() {
	move();	
}

void Shot::render(sf::RenderWindow& window) {
    window.draw(this->sprite);
}

void Shot::die() {
	auto it = std::find(Shot::_shots.begin(), Shot::_shots.end(), this);
	if (it != Shot::_shots.end()) {
		Shot::_shots.erase(it);
	}
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
