#ifndef game_h
#define game_h

#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Window/WindowBase.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics.hpp>
#include "enemy_ship.h"
#include <vector>
#include <memory>
#include "input.h"
#include "enums/shared_state.h"
#include "player_ship.h"

class Game {
public:
	Game(SharedState& state);
	virtual ~Game();
	void update(float dt);
	void render();
	void handleEvents();

	sf::Clock clock;
	const bool running() const;

private:
	sf::RenderWindow *window;
	sf::Event ev;
	sf::VideoMode video_mode;
	Input input;
	SharedState shared_state;

	// TODO: make a class for enemy
	std::vector<std::unique_ptr<EnemyShip>> enemies;
	std::unique_ptr<PlayerShip> player;
	//vector<Shot&> shots;
	sf::Texture maze_tex;
	sf::Sprite maze_sprite;

	void initWindow();
	void initVariables();
	void initEnemies();
	void initMaze();
};


#endif
