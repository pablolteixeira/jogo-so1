#ifndef window_h
#define window_h

#include "input.h"
#include "player_ship.h"
#include "shot.h"
#include "thread/traits.h"
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <memory>
#include <vector>

__BEGIN_API

class Window {
public:
	//Window(sf::RenderWindow& window, Input& input, PlayerShip& player);
	Window(sf::RenderWindow& window);
	void runWindow();

	void setPlayer(PlayerShip *player) { this->player = player; }
	void setInput(Input *input) { this->input = input; }

private:
	// this window will render the objects
	sf::RenderWindow& window;

	// textures and sprites for the screen 
	sf::RectangleShape right_frame;
	sf::RectangleShape left_frame;
	sf::Texture maze_tex;
	sf::Sprite maze_sprite;

	// references game objects and logic classes  
	Input* input = nullptr;
	PlayerShip* player = nullptr;
	std::vector<std::unique_ptr<Shot>> shots;

	// helper methods
	void handleKeyboardInput();
	void draw();
	void drawScreen();

	// initializers for the screen objects and others
	void initMaze();
	void initFrames();
};

__END_API

#endif
