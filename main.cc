#include "game.h"
#include <SFML/System/Time.hpp>

int main() {
	SharedState state; 
	Game game(state);

	while (game.running()) {
		game.handleEvents();
		sf::Time dt = game.clock.restart();
		game.update(dt.asSeconds());
		game.render();
	}

	return 0;
}
