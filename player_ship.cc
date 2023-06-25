#include "player_ship.h"
#include "input.h"
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <cstdio>

PlayerShip::PlayerShip(sf::Vector2f position, Direction shipDirection, SharedState& state, Input& input) : shared_state(state), input(input) {
	if (!texture.loadFromFile("sprites/space_ships/space_ship3.png")) {
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
			texture = textures[0];
			break;
		case Direction::DOWN:
			texture = textures[2];
			break;
		case Direction::LEFT:
			texture = textures[1];
			break;
		case Direction::RIGHT:
			texture = textures[3];
			break;
	}

	sprite.setTexture(texture);
	sprite.setScale(0.5f, 0.5f);
	this->position = position;
	sprite.setPosition(position);

	speed = 150.f;
	shootDelay = 0.5f;
	shootTimer = 0.f;
}

PlayerShip::~PlayerShip() {
	for (auto& shot : playerShots) {
        delete shot;
    }

	for (int i = 0; i < playerShots.size(); i++) {
		playerShots.pop_back();
	}
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
				texture = textures[0];
				sprite.setTexture(texture);
				direction = Direction::UP;
				move(0.f, -20.f);
                break;
            case sf::Keyboard::Down:
				texture = textures[2];
				sprite.setTexture(texture);
				direction = Direction::DOWN;
				move(0.f, 20.f);
                break;
            case sf::Keyboard::Left:
				texture = textures[1];
				sprite.setTexture(texture);
				direction = Direction::LEFT;
				move(-20.f, 0.f);
                break;
            case sf::Keyboard::Right:
				texture = textures[3];
				sprite.setTexture(texture);
				direction = Direction::RIGHT;
				move(20.f, 0.f);
                break;
			case sf::Keyboard::Space:
				shoot();
				break;
            // TODO: Handle shooting, pausing, restarting, quitting as necessary
            default:
                break;
        }

		sprite.setPosition(position.x, position.y);
    }
}

void PlayerShip::move(float x, float y) {
	position.x += x;
	position.y += y;
}

void PlayerShip::shoot() {
	Shot* shot = new Shot(position.x, position.y, direction);
	
	playerShots.push_back(shot);
}

void PlayerShip::updateShots() {
	for (auto& shot : playerShots) {
		shot->update();
	}
}

void PlayerShip::renderShots(sf::RenderWindow& window) {
	for (auto& shot : playerShots) {
		shot->render(window);
	}
}