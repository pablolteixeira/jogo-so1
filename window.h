#ifndef window_h
#define window_h

#include "enemy_ship.h"
#include "input.h"
#include "player_ship.h"
#include "shot.h"
#include "shot_group.h"
#include "thread/traits.h"
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <memory>
#include <vector>

__BEGIN_API

class Window {
public:
	Window(sf::RenderWindow& window);
	void runWindow();

	void setPlayer(PlayerShip *player) { this->player = player; }
	void setInput(Input *input) { this->input = input; }
	void setShotGroup(ShotGroup* shot_group) { this->shot_group = shot_group; }
	void addShot(std::unique_ptr<Shot> shot) {
		shot_group->addShot(std::move(shot));
	}
	void addEnemy(std::shared_ptr<EnemyShip> enemy) {
		enemies.push_back(enemy);
	} 

	// helper methods for the other classes, mainly enemy
	int getGameVelocity() {
		return wave_velocity;
	}
	void lowerPlayerLives() {
		if (player->lives == 0) {
			player->lives--;
		}
	}
	void increasePlayerScore() {
		std::cout << "increased player score to " << player->score << std::endl;
		player->increaseScore();
	}
	
	sf::FloatRect getPlayerBounds() {
		return player->sprite.getGlobalBounds();
	}

	sf::Vector2f getPlayerPosition() {
		return player->sprite.getPosition();
	}

	void setPlayerPosition(float x, float y) {
		player->sprite.setPosition(x, y);
	}

	void decreasePlayerLives() {
		player->lives--;
	}

	void reset() {
		initMaze();
		initFrames();
		initScorePanel();
		player->reset();
		isRunning = true;
		isStopped = false;
		wave_velocity = 0;
	}

	void setStopped() {
		isStopped = true;
	}

	bool getIsStopped() {
		return isStopped;
	}

	void stopRunning() {
		isRunning = false;
	}

	bool getIsRunning() {
		return isRunning;
	}

	void updateVelocityCounter() {
		if (++velocity_counter % 4 == 0) {
			std::cout << "velocity counter updated " << velocity_counter << std::endl;
			wave_velocity++;
			if (wave_velocity > 3) {
				wave_velocity = 3;
			}
		}
		velocity_counter %= 4;
	}

	bool isPaused = false;
	
	// public attributes for convenience
	std::vector<std::shared_ptr<EnemyShip>> enemies;
	sf::RectangleShape left_frame;
	ShotGroup* shot_group = nullptr;

private:
	// this window will render the objects
	sf::RenderWindow& window;
	int wave_velocity = 0;
	int velocity_counter = 0;
	
	// textures and sprites for the screen 
	sf::RectangleShape right_frame;
	sf::Texture maze_tex;
	sf::Sprite maze_sprite;
    sf::Text playerLivesText;
    sf::Text scoreText;
    sf::Text velocityText;
    sf::Font font;

	// variable to make sure windows is running
	bool isRunning;
	bool isStopped;

	// references game objects and logic classes  
	Input* input = nullptr;
	PlayerShip* player = nullptr;

	// helper methods
	void handleKeyboardInput();
	void draw();
	void drawScreen();
	void drawShots();
	void drawEnemies();
	void drawScorePanel();

	// initializers for the screen objects and others
	void initMaze();
	void initFrames();
	void initScorePanel();
};

__END_API

#endif
