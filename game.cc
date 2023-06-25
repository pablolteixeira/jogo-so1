#include "game.h"
#include "enums/direction.h"
#include "player_ship.h"
#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <iostream>
#include <sys/stat.h>
#include <vector>

Game::Game(SharedState& state) {
	initVariables();
	initWindow();
	initEnemies();
	initMaze();

	shared_state = state;
	shared_state.running = true;
}

Game::~Game() {
	delete this->window;
}

void Game::initMaze()
{
    maze_tex.loadFromFile("sprites/maze/screen.png");
    maze_sprite.setTexture(maze_tex);
    maze_sprite.scale(1.5, 1.5);

	player = std::make_unique<PlayerShip>(sf::Vector2f(400.f, 300.f), Direction::UP, shared_state, input);
}

const bool Game::running() const {
	return window->isOpen();
}

void Game::update(float dt) {
	//player->update(dt);
	player->update();
	for (auto& enemy : enemies) {
		enemy->update(dt);	
	}
}

void Game::render() {
	window->clear(sf::Color::White);

	window->draw(maze_sprite); 

	player->render(*window);
	for (auto& enemy : enemies) {
		enemy->render(*window);
	}

	window->display();
}

void Game::initVariables() {
	this->window = nullptr;
}

std::map<sf::Keyboard::Key, std::string> keyMap = {
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

void Game::handleEvents() {
	while (window->pollEvent(ev)) {
		switch (ev.type) {
			case sf::Event::Closed:
				printf("polling event -- closed \n");
				//end();
				window->close();
				break;
			case sf::Event::KeyPressed:
				printf("polling event -- key pressed\n");
				if (keyMap.find(ev.key.code) != keyMap.end()) {
					printf("Key name: %s\n", keyMap[ev.key.code].c_str());
				} else {
					printf("Key name: Unknown\n");
				}
				input.pushEvent(ev.key);
				printf("is input empty? %d\n", input.key_event_queue.empty());
				break;
			default:
				break;
		}
	}
}

void Game::initWindow() {
	this->video_mode.height = 600;
	this->video_mode.width = 800;
	this->window = new sf::RenderWindow(video_mode, "SFML GAME", sf::Style::Titlebar | sf::Style::Close);
	window->setFramerateLimit(60);
}

void Game::initEnemies() {
	std::vector<sf::Vector2f> positions = {
		sf::Vector2f(100.f, 100.f),
		sf::Vector2f(700.f, 100.f), 
		sf::Vector2f(100.f, 500.f),
		sf::Vector2f(700.f, 500.f)
	};

	std::vector<Direction> directions = {
		Direction::DOWN, Direction::DOWN, Direction::UP, Direction::UP
	};

	for (int i = 0; i < 4; i++) {
		std::unique_ptr<EnemyShip> enemy = std::make_unique<EnemyShip>(positions[i], directions[i]);
		enemies.push_back(std::move(enemy));
	}
}




