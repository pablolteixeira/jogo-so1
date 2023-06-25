#include "game.h"
#include <SFML/System/Time.hpp>

int main() {
	SharedState state; 
	Game game(state);

	while (game.running()) {
		game.handleEvents();
		game.handleInput();

		sf::Time dt = game.clock.restart();

		if (!game.isPaused) {
			game.update(dt.asSeconds());
			game.render();
		}
	}

	return 0;
}
