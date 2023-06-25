#include "player_ship.h"
#include "enums/direction.h"
#include "input.h"
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <cstdio>

PlayerShip::PlayerShip(sf::Vector2f position, Direction shipDirection, SharedState& state, Input& input) : shared_state(state), input(input) {
	if (!this->texture.loadFromFile("sprites/space_ships/space_ship3.png")) {
		exit(1);
	}

	textures = {};
	for (int i = 1; i <= 4; i++) {
		sf::Texture tex;
		std::string filePath = "sprites/space_ships/space_ship" + std::to_string(i) + ".png";
		if (!tex.loadFromFile(filePath)) {
			exit(1);
		}
		textures.push_back(tex);
	}

	switch (shipDirection) {
		case Direction::UP:
			this->texture = textures[0];
			break;
		case Direction::DOWN:
			this->texture = textures[2];
			break;
		case Direction::LEFT:
			this->texture = textures[1];
			break;
		case Direction::RIGHT:
			this->texture = textures[3];
			break;
	}

	changeDirection(shipDirection);

	this->sprite.setTexture(texture);
	this->sprite.setScale(0.5f, 0.5f);
	this->sprite.setPosition(position);

	this->speed = 150.f;
	this->shootDelay = 0.5f;
	this->shootTimer = 0.f;
}

PlayerShip::~PlayerShip() {

};

void PlayerShip::changeDirection(Direction direction) {
	this->direction = direction;
	switch (direction) {
		case Direction::UP:
			this->texture = textures[0];
			this->sprite.setTexture(texture);
			directionVector = sf::Vector2f(0.f, -1.f);
			break;
		case Direction::DOWN: 
			this->texture = textures[2];
			this->sprite.setTexture(texture);
			directionVector = sf::Vector2f(0.f, 1.f);
			break;
		case Direction::LEFT: 
			this->texture = textures[1];
			this->sprite.setTexture(texture);
			directionVector = sf::Vector2f(-1.f, 0.f);
			break;
		case Direction::RIGHT:
			this->texture = textures[3];
			this->sprite.setTexture(texture);
			directionVector = sf::Vector2f(1.f, 0.f);
			break;
	}
}


void PlayerShip::update(float dt) {
	getUserInput();	
	move(dt);
}

void PlayerShip::render(sf::RenderWindow& window) {
    window.draw(this->sprite);
}

void PlayerShip::getUserInput() {
    sf::Keyboard::Key key;
    while (input.tryPopKey(key)) {
        switch(key) {
            case sf::Keyboard::Up:
				changeDirection(Direction::UP);
                break;
            case sf::Keyboard::Down:
				changeDirection(Direction::DOWN);
                break;
            case sf::Keyboard::Left:
				changeDirection(Direction::LEFT);
                break;
            case sf::Keyboard::Right:
				changeDirection(Direction::RIGHT);
                break;
			case sf::Keyboard::Space:
				shoot();
				break;
            // TODO: Handle shooting, pausing, restarting, quitting as necessary
            default:
                break;
        }
    }
}

void PlayerShip::increaseScore() {
	this->score += 100;
}

void PlayerShip::move(float dt) {
	sprite.move(directionVector * speed * dt);
}

void PlayerShip::shoot() {
    float shotWidth = sprite.getGlobalBounds().width / 3.0f;
    float shotHeight = sprite.getGlobalBounds().height / 3.0f;

    float playerCenterX = sprite.getPosition().x + sprite.getGlobalBounds().width / 2.0f;
    float playerCenterY = sprite.getPosition().y + sprite.getGlobalBounds().height / 2.0f;

    float shotStartX = playerCenterX - shotWidth / 2.0f;
    float shotStartY = playerCenterY - shotHeight / 2.0f;

    Shot* shot = new Shot(shotStartX, shotStartY, this->direction, ShipType::PLAYER, 320.f);
    Shot::_shots.push_back(shot);
}


