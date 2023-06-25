#include "shot.h"
#include "enums/ship_type.h"
#include "player_ship.h"
#include <SFML/System/Vector2.hpp>
#include <iostream>
#include <vector>

std::vector<Shot*> Shot::_shots;

Shot::Shot(float startX, float startY, Direction direction, ShipType shipType, float speed) {
    this->position.x = startX;
    this->position.y = startY;
    this->direction = direction;
    this->ship_type = shipType;
	this->speed = speed;

    this->texture.loadFromFile("sprites/space_ships/shot.png");
    this->sprite.setTexture(this->texture);
    this->sprite.scale(0.5f, 0.5f);
    this->sprite.setPosition(this->position);

	Shot::_shots.push_back(this);
}

Shot::~Shot() {
}

void Shot::move(float dt) {
    sprite.move(directionVector * speed * dt);
}

void Shot::update(float dt) {
    switch (direction)
    {
    case Direction::UP:
		directionVector = sf::Vector2f(0.f, -1.f);
        break;
    case Direction::DOWN:
		directionVector = sf::Vector2f(0.f, 1.f);
        break;
    case Direction::RIGHT:
		directionVector = sf::Vector2f(1.f, 0.f);
        break;
    case Direction::LEFT:
		directionVector = sf::Vector2f(-1.f, 0.f);
        break;
    default:
        break;
    }
	
	move(dt);
}

void Shot::render(sf::RenderWindow& window) {
    window.draw(this->sprite);
}

void Shot::die() {
	auto it = std::find(Shot::_shots.begin(), Shot::_shots.end(), this);
	if (it != Shot::_shots.end()) {
		Shot::_shots.erase(it);
	}
	std::cout << "shot died fr\n";
}

void Shot::updateShots(float dt) {
	for (auto& shot : Shot::_shots) {
		shot->update(dt);
	}
}

void Shot::renderShots(sf::RenderWindow& window) {
	for (auto& shot : Shot::_shots) {
		shot->render(window);
	}
}
