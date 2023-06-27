#include "game.h"
#include "enemy_ship.h"
#include "enums/algorithm.h"
#include "enums/direction.h"
#include "input.h"
#include "player_ship.h"
#include "shot_group.h"
#include "thread/debug.h"
#include "thread/traits.h"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <iostream>
#include <memory>
#include <ostream>
#include <sys/stat.h>
#include <vector>
#include "thread/thread.h"
#include "window.h"

__BEGIN_API

std::unique_ptr<sf::RenderWindow> Game::render_window = nullptr;
std::unique_ptr<Input> Game::input = nullptr;
std::unique_ptr<PlayerShip> Game::player = nullptr;
std::unique_ptr<Window> Game::window = nullptr;
std::unique_ptr<ShotGroup> Game::shot_group = nullptr;
std::vector<std::unique_ptr<EnemyShip>> enemies = {};
std::unique_ptr<CollisionHandler> Game::collision_handler = nullptr;

Thread* Game::player_thread = nullptr;
Thread* Game::window_thread = nullptr;
Thread* Game::input_thread = nullptr;
Thread* Game::shot_group_thread = nullptr;
std::vector<Thread*> Game::enemy_threads = {};
Thread* Game::collision_handler_thread = nullptr;

std::vector<sf::Vector2f> Game::enemy_positions {
	sf::Vector2f(100.f, 100.f),
	sf::Vector2f(300.f, 100.f), 
	sf::Vector2f(100.f, 500.f),
	sf::Vector2f(300.f, 500.f)
};
std::vector<Direction> Game::enemy_directions = {
	Direction::DOWN, Direction::DOWN, Direction::UP, Direction::UP
};
std::vector<Algorithm> Game::enemy_algorithms = {
	Algorithm::FOLLOW_PLAYER, Algorithm::SNIPER
};
int Game::enemy_id = 0;

Game::Game() {
}

Game::~Game() {
	// FIXME: there was a delete this->window; here before
}

void Game::runPlayer() {	
	std::cout << "RUN PLAYEr\n";
	db<System>(TRC) << "Game::runPlayer() started\n";

	player = std::make_unique<PlayerShip>(sf::Vector2f(400.f, 300.f), Direction::UP);
	player->setWindow(window.get());
	window->setPlayer(player.get());
		
	// TODO: player->attachWindow? window->attachShip?
	player->run();
	player_thread->thread_exit(3);
}

void Game::runInput() {
	std::cout << "RUN INPUT\n";
	input = std::make_unique<Input>(*render_window.get());
	input->setWindow(window.get());
	window->setInput(input.get());
	input->runInput();
	input_thread->thread_exit(2);
}

void Game::runWindow() {
	std::cout << "RUN WINDOW\n";
	window = std::make_unique<Window>(*render_window.get());
	window->runWindow();
	window_thread->thread_exit(1);
}

void Game::runShotGroup() {
	shot_group = std::make_unique<ShotGroup>();
	shot_group->setWindow(window.get());
	shot_group->runShots();
	shot_group_thread->thread_exit(4);
}

void Game::runEnemy() {
	std::shared_ptr<EnemyShip> enemy = std::make_shared<EnemyShip>(enemy_positions[enemy_id], enemy_directions[enemy_id], enemy_algorithms[enemy_id % 2]);	
	enemy->setWindow(window.get());
	window->addEnemy(enemy);
	enemy_id++;
	enemy->run();
	enemy_threads[enemy_id-1]->thread_exit(4+enemy_id);
}

void Game::runCollisionHandler() {
	std::unique_ptr<CollisionHandler> collision_handler = std::make_unique<CollisionHandler>();
	collision_handler->setWindow(window.get());
	collision_handler->run();
	collision_handler_thread->thread_exit(9);
}

void Game::run(void *name) {
	db<System>(TRC) << "Game is starting\n";

	// initializing the render window
	sf::VideoMode video_mode;
	// 543x373	
	video_mode.height = 373;
	video_mode.width = 543;
	render_window = std::make_unique<sf::RenderWindow>(video_mode, "SFML GAME", sf::Style::Titlebar | sf::Style::Close);
	render_window->setFramerateLimit(60);
	
	// threading and running the game
	window_thread = new Thread(runWindow);
	input_thread = new Thread(runInput);
	player_thread = new Thread(runPlayer);
	shot_group_thread = new Thread(runShotGroup);
	for (int i = 0; i < 4; i++) {
		enemy_threads.push_back(new Thread(runEnemy));
	}
	collision_handler_thread = new Thread(runCollisionHandler);

	window_thread->join();
	input_thread->join();
	player_thread->join();
	shot_group_thread->join();
	for (auto& thread : enemy_threads) {
		thread->join();
	}
	collision_handler_thread->join();

	delete window_thread;
	delete input_thread;
	delete player_thread;
	delete shot_group_thread;
	for (auto& thread : enemy_threads) {
		delete thread;
	}
	delete collision_handler_thread;

	enemy_threads.clear();

	db<System>(TRC) << "Game ended\n";
}

__END_API

