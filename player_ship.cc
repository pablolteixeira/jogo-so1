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
	sprite.setPosition(position);

	speed = 150.f;
	shootDelay = 0.5f;
	shootTimer = 0.f;
}

PlayerShip::~PlayerShip() {};

void PlayerShip::update() {
	getUserInput();	
}

void PlayerShip::render(sf::RenderWindow& window) {
    window.draw(this->sprite);
}

std::map<sf::Keyboard::Key, std::string> keyMapplayer = {
	{sf::Keyboard::Unknown, "Unknown"},
    {sf::Keyboard::A, "A"},
    {sf::Keyboard::B, "B"},
    {sf::Keyboard::Up, "Up"},
    {sf::Keyboard::Down, "Down"},
    {sf::Keyboard::Left, "Left"},
    {sf::Keyboard::Right, "Right"},
    {sf::Keyboard::Space, "Space"},
    {sf::Keyboard::P, "P"},
    {sf::Keyboard::Q, "Q"},
    {sf::Keyboard::R, "R"},
    //...
};

void PlayerShip::getUserInput() {
    sf::Keyboard::Key key;
    while (input.tryPopKey(key)) {
		printf("trypopkey");
		if (keyMapplayer.find(key) != keyMapplayer.end()) {
			printf("Key name: %s\n", keyMapplayer[key].c_str());
		} else {
			printf("Key name: Unknown\n");
		}
        switch(key) {
            case sf::Keyboard::Up:
				printf("key press up\n");
				texture = textures[0];
				sprite.setTexture(texture);
				move(0.f, -20.f);
                break;
            case sf::Keyboard::Down:
				printf("key press down\n");
				texture = textures[2];
				sprite.setTexture(texture);
				move(0.f, 20.f);
                break;
            case sf::Keyboard::Left:
				printf("key press left\n");
				texture = textures[1];
				sprite.setTexture(texture);
				move(-20.f, 0.f);
                break;
            case sf::Keyboard::Right:
				printf("key press right\n");
				texture = textures[3];
				sprite.setTexture(texture);
				move(20.f, 0.f);
                break;
			case sf::Keyboard::Space:
				printf("YEEHAW!\n");
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
