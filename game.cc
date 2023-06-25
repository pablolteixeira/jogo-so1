#include "game.h"
#include "collision_handler.h"
#include "enums/direction.h"
#include "player_ship.h"
#include "score_panel.h"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <iostream>
#include <sys/stat.h>
#include <vector>

Game::Game(SharedState& state) : score_panel(), collision_handler(*this) {
	initVariables();
	initWindow();
	initMaze();
	initFrames();
	initEnemies();

	shared_state = state;
	shared_state.running = true;
}

Game::~Game() {
	delete this->window;
}

void Game::initFrames() {
	// Left part
    left_frame = sf::RectangleShape(sf::Vector2f(window->getSize().x * 2.f / 3.f, window->getSize().y));
    left_frame.setFillColor(sf::Color::Black);
    left_frame.setOutlineThickness(2); // Border thickness
    left_frame.setOutlineColor(sf::Color::Red); // Border color

    // Right part
    right_frame = sf::RectangleShape(sf::Vector2f(window->getSize().x / 3.f, window->getSize().y));
    right_frame.setPosition(sf::Vector2f(window->getSize().x * 2.f / 3.f, 0));
    right_frame.setFillColor(sf::Color::Black);
    right_frame.setOutlineThickness(2); // Border thickness
    right_frame.setOutlineColor(sf::Color::Blue); // Border color

    window->draw(right_frame);
    window->draw(left_frame);
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
	Shot::updateShots();
	collision_handler.checkShipBorderCollision(*player);

	for (auto& shot : Shot::_shots) {
		collision_handler.checkShotBorderCollision(*shot);
	}

	for (auto& enemy : enemies) {
		enemy->update(dt);
		collision_handler.checkPlayerEnemyCollision(*player, *enemy);
		collision_handler.checkShipBorderCollision(*enemy);
	}

	score_panel.update(player->lives, player->score, wave_velocity);
}

void Game::render() {
	window->clear(sf::Color::White);

	window->draw(maze_sprite); 

	window->draw(right_frame);
	window->draw(left_frame);

	player->render(*window);
	Shot::renderShots(*window);
	for (auto& enemy : enemies) {
		enemy->render(*window);
	}

	score_panel.render(*window);

	window->display();
}

void Game::initVariables() {
	this->window = nullptr;
}

void Game::handleEvents() {
	while (window->pollEvent(ev)) {
		switch (ev.type) {
			case sf::Event::Closed:
				//end();
				window->close();
				break;
			case sf::Event::KeyPressed:
				input.pushEvent(ev.key);
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
	std::cout << "INITENEMIES\n";
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
		std::unique_ptr<EnemyShip> enemy = std::make_unique<EnemyShip>(positions[i], directions[i], player.get());
		enemies.push_back(std::move(enemy));
	}
	std::cout << "end -- initenemies\n";
}

