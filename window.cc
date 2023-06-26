
#include "window.h"
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
	this->isRunning = true;
};

Window::~Window() {

}

void Window::runWindow() {
	while (this->getIsRunning()) {
		if (input == nullptr || player == nullptr) {
			Thread::yield();
		}
		handleKeyboardInput();
		draw();
		Thread::yield();
	}
}

void Window::finishWindow() {
	this->isRunning = false;
}

bool Window::getIsRunning() {
	return this->isRunning;
}

void Window::handleKeyboardInput() {
	//std::cout << "handle keyboard input\n" << std::flush;

	sf::Keyboard::Key key;
	
	if (input->tryPopKey(key)) {
		//std::cout << "inside if try pop key\n" << std::flush;
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
			finishWindow();
		} else if (key == sf::Keyboard::R) {
			
		}
	}
}

void Window::draw() {
	window.clear();
	drawScreen();
	window.draw(player->sprite);
	window.display();
}

void Window::drawScreen() {
	window.draw(right_frame);
	window.draw(left_frame);
	window.draw(maze_sprite);
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

__END_API
