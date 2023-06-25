#ifndef game_h
#define game_h

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/VideoMode.hpp>
//#include <SFML/Window/WindowBase.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics.hpp>
#include "collision_handler.h"
#include "enemy_ship.h"
#include <vector>
#include <memory>
#include "input.h"
#include "enums/shared_state.h"
#include "player_ship.h"
#include "score_panel.h"
#include "shot.h"

class Game {
public:
	Game(SharedState& state);
	virtual ~Game();
	void update(float dt);
	void render();
	void handleEvents();
	void updateVelocityCounter();
	int velocity_counter = 0;
	int wave_velocity = 1;

	sf::Clock clock;
	const bool running() const;
	std::vector<std::unique_ptr<EnemyShip>> enemies;

	sf::RectangleShape left_frame;
	sf::RectangleShape right_frame;

private:
	sf::RenderWindow *window;
	sf::Event ev;
	sf::VideoMode video_mode;
	Input input;
	SharedState shared_state;
	ScorePanel score_panel;
	CollisionHandler collision_handler;

	std::unique_ptr<PlayerShip> player;

	//vector<Shot&> shots;
	sf::Texture maze_tex;
	sf::Sprite maze_sprite;

	void initFrames();
	void initWindow();
	void initVariables();
	void initEnemies();
	void initMaze();
};


#endif
