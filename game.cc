#include "game.h"
#include "game_objects/game_object.h"
#include <vector>

// Game.cpp
void Game::update(float dt) {
    // Update player ship
    if (player_ship != nullptr) {
        player_ship->update(dt);
    }

    // Update enemy ships
    for (auto& enemy_ship : enemy_ships) {
        if (enemy_ship != nullptr) {
            enemy_ship->update(dt);
        }
    }

    // Update shots
    for (auto& shot : shots) {
        if (shot != nullptr) {
            shot->update(dt);
        }
    }

    // Update score panel
    if (score_panel != nullptr) {
        score_panel->update();
    }

    // Check for collisions
    if (collision_handler != nullptr) {
        collision_handler->checkCollisions();
    }
}

void Game::draw() {
    // Draw player ship
    if (player_ship != nullptr) {
        player_ship->draw(window);
    }

    // Draw enemy ships
    for (auto& enemy_ship : enemy_ships) {
        if (enemy_ship != nullptr) {
            enemy_ship->draw(window);
        }
    }

    // Draw shots
    for (auto& shot : shots) {
        if (shot != nullptr) {
            shot->draw(window);
        }
    }

    // Draw score panel
    if (score_panel != nullptr) {
        score_panel->draw(window);
    }
}

void Game::run() {
	// Game setup...
	// This might include creating the window, initializing the player spaceship, 
	// spawning initial enemy spaceships, setting up the score panel, etc.

	// Main game loop
	while (window.isOpen() && is_running) {
		// Handle events
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}

		float deltaTime = clock.restart().asSeconds();

		player_ship->update(deltaTime);  
		for(auto &enemy : enemy_ships) {
			enemy->update(deltaTime);  
		}
		for(auto &shot : shots) {
			shot->update(deltaTime);  
		}

		collision_handler->checkCollisions();  

		score_panel->update();

		if (player_ship->isDead()) {
			is_running = false;
		}

		window.clear();
		player_ship->draw(window);
		for(auto &enemy : enemy_ships) {
			enemy->draw(window);
		}
		for(auto &shot : shots) {
			shot->draw(window);
		}
		score_panel->draw(window);
		window.display();
	}

	// TODO: game cleanup (game over screen, cleaning up resources)
	// This might involve showing a game over screen, cleaning up resources, etc.
}
