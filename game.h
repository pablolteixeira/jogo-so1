#ifndef game_h
#define game_h

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include "input.h"
#include "player_ship.h"
#include "thread/thread.h"
#include "thread/traits.h"
#include "window.h"

__BEGIN_API

class Game {
public:
	Game();
	~Game();
	static void run(void *name);

private:
	static std::unique_ptr<sf::RenderWindow> render_window;
	static std::unique_ptr<Input> input;
	static std::unique_ptr<PlayerShip> player;
	static std::unique_ptr<Window> window;

	static Thread* player_thread;
	static Thread* window_thread;
	// TODO: vector for the enemy threads?
	static Thread* input_thread;

	static void runPlayer();
	static void runWindow();
	static void runInput();
};

__END_API

#endif
