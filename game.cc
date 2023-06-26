#include "game.h"
#include "enums/direction.h"
#include "input.h"
#include "player_ship.h"
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

Thread* Game::player_thread = nullptr;
Thread* Game::window_thread = nullptr;
Thread* Game::input_thread = nullptr;

Game::Game() {
}

Game::~Game() {
	// FIXME: there was a delete this->window; here before
}

void Game::runPlayer() {	
	//std::cout << "runplayer\n" << std::flush;
	db<System>(TRC) << "Game::runPlayer() started\n";

	player = std::make_unique<PlayerShip>(sf::Vector2f(400.f, 300.f), Direction::UP);
	player->setWindow(window.get());
	window->setPlayer(player.get());
		
	// TODO: player->attachWindow? window->attachShip?
	player->run();
	player_thread->thread_exit(2);
}

void Game::runInput() {
	//std::cout << "run input\n" << std::flush;
	input = std::make_unique<Input>(*render_window.get());
	input->setWindow(window.get());
	window->setInput(input.get());

	input->runInput();
	input_thread->thread_exit(1);
}

void Game::runWindow() {
	window = std::make_unique<Window>(*render_window.get());
	window->runWindow();
	window_thread->thread_exit(3);
}

void Game::run(void *name) {
	db<System>(TRC) << "Game is starting\n";

	// initializing the render window
	sf::VideoMode video_mode;
	video_mode.height = 560;
	video_mode.width = 815;
	render_window = std::make_unique<sf::RenderWindow>(video_mode, "SFML GAME", sf::Style::Titlebar | sf::Style::Close);
	render_window->setFramerateLimit(60);
	
	// threading and running the game
	window_thread = new Thread(runWindow);
	input_thread = new Thread(runInput);
	player_thread = new Thread(runPlayer);

	window_thread->join();
	input_thread->join();
	player_thread->join();


	delete window_thread;
	delete input_thread;
	delete player_thread;

	db<System>(TRC) << "Game ended\n";
}

//void Game::update(float dt) {	
//	player->update(dt);
//	Shot::updateShots(dt);
//	collision_handler.checkShipBorderCollision(*player);
//
//	for (auto& shot : Shot::_shots) {
//		collision_handler.checkShotBorderCollision(*shot);
//		for (auto& shot2 : Shot::_shots) {
//			if (shot != shot2)
//			collision_handler.checkShotShotCollision(*shot, *shot2);
//		}
//	}
//
//	for (auto& enemy : enemies) {
//		enemy->update(dt, *this, window->getSize(), wave_velocity);
//		collision_handler.checkPlayerEnemyCollision(*player, *enemy);
//		collision_handler.checkShipBorderCollision(*enemy);
//		for (auto& enemy2 : enemies) {
//			collision_handler.checkEnemyEnemyCollision(*enemy, *enemy2);
//		}
//	}
//
//	for (Shot* shot : Shot::_shots) {
//		collision_handler.checkShotShipCollision(*shot, *player);	
//		for (auto& enemy : enemies) {
//			collision_handler.checkShotShipCollision(*shot, *player, *enemy);
//		}
//	}
//	Shot::cleanUpShots();
//
//	score_panel.update(player->lives, player->score, wave_velocity);
//}

//void Game::render() {
//	window->clear(sf::Color::White);
//
//	window->draw(maze_sprite); 
//
//	window->draw(right_frame);
//	window->draw(left_frame);
//
//	player->render(*window);
//	Shot::renderShots(*window);
//	for (auto& enemy : enemies) {
//		enemy->render(*window);
//	}
//
//	score_panel.render(*window);
//
//	window->display();
//}

//void Game::initVariables() {
//	this->window = nullptr;
//}
//
//void Game::handleEvents() {
//	while (window->pollEvent(ev)) {
//		switch (ev.type) {
//			case sf::Event::Closed:
//				window->close();
//				break;
//			case sf::Event::KeyPressed:
//				input.pushEvent(ev.key);
//				break;
//			default:
//				break;
//		}
//	}
//}
//
//void Game::handleInput() {
//	sf::Keyboard::Key key;
//	if (input.tryPopKey(key)) {
//		if (key == sf::Keyboard::Up || key == sf::Keyboard::Down || 
//			key == sf::Keyboard::Left || key == sf::Keyboard::Right ||
//			key == sf::Keyboard::Space) 
//		{
//			this->player->getUserInput(key);
//		} else if (key == sf::Keyboard::P) {
//			this->isPaused = !this->isPaused;
//		} else if (key == sf::Keyboard::Q) {
//			this->window->close();
//		} else if (key == sf::Keyboard::R) {
//			
//		}
//	}
//}
//
//void Game::initWindow() {
//	this->video_mode.height = 600;
//	this->video_mode.width = 800;
//	this->window = new sf::RenderWindow(video_mode, "SFML GAME", sf::Style::Titlebar | sf::Style::Close);
//	window->setFramerateLimit(60);
//}
//
//void Game::updateVelocityCounter() {
//	if (++velocity_counter % 4 == 0) {
//		std::cout << "velocity counter updated " << velocity_counter << std::endl;
//		wave_velocity++;
//		if (wave_velocity > 3) {
//			wave_velocity = 3;
//		}
//	}
//	velocity_counter %= 4;
//}
//
//void Game::initEnemies() {
//	std::vector<sf::Vector2f> positions = {
//		sf::Vector2f(100.f, 100.f),
//		sf::Vector2f(700.f, 100.f), 
//		sf::Vector2f(100.f, 500.f),
//		sf::Vector2f(700.f, 500.f)
//	};
//
//	std::vector<Direction> directions = {
//		Direction::DOWN, Direction::DOWN, Direction::UP, Direction::UP
//	};
//
//	std::vector<Algorithm> algorithms = {
//		Algorithm::FOLLOW_PLAYER, Algorithm::SNIPER
//	};
//
//	for (int i = 0; i < 4; i++) {
//		std::unique_ptr<EnemyShip> enemy = std::make_unique<EnemyShip>(positions[i], directions[i], player.get(), algorithms[i % 2]);
//		enemies.push_back(std::move(enemy));
//	}
//}

__END_API

