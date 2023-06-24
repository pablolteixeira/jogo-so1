#include "game.h"
#include "game_objects/player_spaceship.h"
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>
#include <vector>

Game::Game(sf::RenderWindow& window) : window(window), player(std::make_unique<PlayerSpaceship>()), input(std::make_unique<Input>(*player, window)) {
	clock = new sf::Clock();
}

Game::~Game() {
	delete clock;
}

void Game::handleEvent(const sf::Event& event) {
    input->processEvent(event);
}

void Game::run() {
    sf::Clock clock;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            input->processEvent(event);
        }
        
        float deltaTime = clock.restart().asSeconds();

        player->update(deltaTime);
        window.clear();
        player->draw(window);
        window.display();
    }
}

sf::Time Game::getElapsedTime() const {
    return clock->getElapsedTime();
}

void Game::restartClock() {
    clock->restart();
}
