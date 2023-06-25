#include "player_ship.h"
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

	this->sprite.setTexture(texture);
	this->sprite.setScale(0.5f, 0.5f);
	this->position = position;
	this->sprite.setPosition(position);

	this->speed = 150.f;
	this->shootDelay = 0.5f;
	this->shootTimer = 0.f;
}

PlayerShip::~PlayerShip() {

};

void PlayerShip::update() {
	getUserInput();	
}

void PlayerShip::render(sf::RenderWindow& window) {
    window.draw(this->sprite);
}

void PlayerShip::getUserInput() {
    sf::Keyboard::Key key;
    while (input.tryPopKey(key)) {
        switch(key) {
            case sf::Keyboard::Up:
				this->texture = textures[0];
				this->sprite.setTexture(texture);
				this->direction = Direction::UP;
				move(0.f, -20.f);
                break;
            case sf::Keyboard::Down:
				this->texture = textures[2];
				this->sprite.setTexture(texture);
				this->direction = Direction::DOWN;
				move(0.f, 20.f);
                break;
            case sf::Keyboard::Left:
				this->texture = textures[1];
				this->sprite.setTexture(texture);
				this->direction = Direction::LEFT;
				move(-20.f, 0.f);
                break;
            case sf::Keyboard::Right:
				this->texture = textures[3];
				this->sprite.setTexture(texture);
				this->direction = Direction::RIGHT;
				move(20.f, 0.f);
                break;
			case sf::Keyboard::Space:
				shoot();
				break;
            // TODO: Handle shooting, pausing, restarting, quitting as necessary
            default:
                break;
        }

		this->sprite.setPosition(position);
    }
}

void PlayerShip::move(float x, float y) {
	this->position.x += x;
	this->position.y += y;
}

void PlayerShip::shoot() {
	Shot* shot = new Shot(this->position.x, this->position.y, this->direction, ShipType::PLAYER);
	
	Shot::_shots.push_back(shot);
}