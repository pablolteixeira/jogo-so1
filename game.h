#ifndef game_h
#define game_h

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include "enemy_ship.h"
#include "enums/algorithm.h"
#include "enums/direction.h"
#include "input.h"
#include "player_ship.h"
#include "shot_group.h"
#include "thread/thread.h"
#include "thread/traits.h"
#include "window.h"
#include "collision_handler.h"

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
	static std::unique_ptr<ShotGroup> shot_group;
	static std::unique_ptr<CollisionHandler> collision_handler;

	static Thread* player_thread;
	static Thread* window_thread;
	// TODO: vector for the enemy threads?
	static Thread* input_thread;
	static Thread* shot_group_thread;
	static std::vector<Thread*> enemy_threads;
	static Thread* collision_handler_thread;

	static void runPlayer();
	static void runWindow();
	static void runInput();
	static void runShotGroup();
	static void runEnemy();
	static void runCollisionHandler();

	static std::vector<sf::Vector2f> enemy_positions;
	static std::vector<Algorithm> enemy_algorithms;
	static std::vector<Direction> enemy_directions;
	static int enemy_id;
};

__END_API

#endif
