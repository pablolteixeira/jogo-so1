
#include "window.h"
#include "shot.h"
#include "thread/thread.h"
#include "thread/traits.h"
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Keyboard.hpp>

__BEGIN_API

Window::Window(sf::RenderWindow& window)
	: window(window) 
{
	initMaze();
	initFrames();
	initScorePanel();
};

void Window::runWindow() {
	// FIXME: change while(true) to while(is game running)
	while (true) {
		if (input == nullptr || player == nullptr) {
			Thread::yield();
		}
		handleKeyboardInput();
		draw();
		Thread::yield();
	}
}

void Window::handleKeyboardInput() {
	sf::Keyboard::Key key;
	
	if (input->tryPopKey(key)) {
		if (key == sf::Keyboard::Up || key == sf::Keyboard::Down || 
			key == sf::Keyboard::Left || key == sf::Keyboard::Right ||
			key == sf::Keyboard::Space)
		{
			player->setUserKeyPress(key);
		} else if (key == sf::Keyboard::P) {
			// TODO: isPaused on P 
			//isPaused = !this->isPaused;
		} else if (key == sf::Keyboard::Q) {
			// FIXME: need to close the game instead of just closing the window
			window.close();
		} else if (key == sf::Keyboard::R) {
			
		}
	}
}

void Window::draw() {
	window.clear();
	drawScreen();
	drawEnemies();
	drawShots();
	drawScorePanel();
	window.draw(player->sprite);
	window.display();
}

void Window::drawShots() {
	for (auto& shot : shot_group->shots) {
		window.draw(shot->sprite);
	}
}

void Window::drawEnemies() {
	for (auto& enemy : enemies) {
		if (enemy->isAlive)
		window.draw(enemy->sprite);
	}
}

void Window::drawScreen() {
	window.draw(right_frame);
	window.draw(left_frame);
	window.draw(maze_sprite);
}

void Window::drawScorePanel() {
    playerLivesText.setString("Lives: " + std::to_string(player->lives));
    scoreText.setString("Score: " + std::to_string(player->score));
    velocityText.setString("Velocity: " + std::to_string(wave_velocity));
    window.draw(playerLivesText);
    window.draw(scoreText);
    window.draw(velocityText);
}

void Window::initFrames() {
	left_frame = sf::RectangleShape(sf::Vector2f(window.getSize().x * 2.f / 3.f, window.getSize().y));
    left_frame.setFillColor(sf::Color::Black);
    left_frame.setOutlineThickness(2); // Border thickness
    left_frame.setOutlineColor(sf::Color::Red); // Border color
	
	right_frame = sf::RectangleShape(sf::Vector2f(window.getSize().x / 3.f, window.getSize().y));
    right_frame.setPosition(sf::Vector2f(window.getSize().x * 2.f / 3.f, 0));
    right_frame.setFillColor(sf::Color::Black);
    right_frame.setOutlineThickness(2); // Border thickness
    right_frame.setOutlineColor(sf::Color::Blue); // Border color
}

void Window::initMaze() {
    maze_tex.loadFromFile("sprites/maze/screen.png");
    maze_sprite.setTexture(maze_tex);
    maze_sprite.scale(1.5, 1.5);
}

void Window::initScorePanel() {
	// Load font
    if (!this->font.loadFromFile("fonts/free_sans_bold.otf")) { // Adjust the file path as necessary
        std::cout << "Failed to load font\n";
        exit(1);
    }

    // Initialize text objects
    this->playerLivesText.setFont(this->font);
    this->playerLivesText.setCharacterSize(24); // adjust the size as you like
    this->playerLivesText.setFillColor(sf::Color::White); // color
    this->playerLivesText.setPosition(600.f, 20.f); // set position near right side of the window

    this->scoreText.setFont(this->font);
    this->scoreText.setCharacterSize(24);
    this->scoreText.setFillColor(sf::Color::White);
    this->scoreText.setPosition(600.f, 60.f);

    this->velocityText.setFont(this->font);
    this->velocityText.setCharacterSize(24);
    this->velocityText.setFillColor(sf::Color::White);
    this->velocityText.setPosition(600.f, 100.f);
}

__END_API


