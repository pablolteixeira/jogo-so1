#include "shot.h"
#include "enums/direction.h"
#include "enums/ship_type.h"
#include "thread/traits.h"
#include <SFML/System/Vector2.hpp>
#include <iostream>
#include <vector>

__BEGIN_API

Shot::Shot(float startX, float startY, Direction direction, ShipType shipType, float speed) {
    this->position.x = startX;
    this->position.y = startY;
    this->direction = direction;
    this->ship_type = shipType;
	this->speed = speed;
    this->isDead = false;

    this->texture.loadFromFile("sprites/space_ships/shot.png");
    this->sprite.setTexture(this->texture);
    this->sprite.scale(0.5f, 0.5f);
    this->sprite.setPosition(this->position);
}

Shot::~Shot() {
}

void Shot::move(float dt) {
    sprite.move(directionVector * speed * dt);
	sf::Vector2f result = directionVector * speed * dt;
	std::cout << "\n\nnew shot x: "<<result.x<<std::endl;
	std::cout << "\n\nnew shot y: "<<result.y<<std::endl;
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

void Shot::die() {

}

//void Shot::cleanUpShots() {
//    // Remover todos os objetos mortos do vetor
//    Shot::_shots.erase(
//        std::remove_if(
//            Shot::_shots.begin(),
//            Shot::_shots.end(),
//            [](Shot* shot) { return shot->isDead; }
//        ),
//        Shot::_shots.end()
//    );
//}

__END_API
