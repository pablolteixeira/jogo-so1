#ifndef input_h
#define input_h

#include "game_objects/player_spaceship.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

class Input {
public:
	Input(PlayerSpaceship& player, sf::RenderWindow& window) : player(player), window(window) {}
	
    void processEvent(const sf::Event& event) {
		switch (event.type) {
			case sf::Event::KeyPressed:
				notifyPlayer(event.key.code);
				break;
			case sf::Event::Closed:
				window.close();
				break;
			default:
				break;
		}
    }

private:
    void notifyPlayer(sf::Keyboard::Key key) {
        player.handleInput(key);
    }

	sf::RenderWindow& window;
    PlayerSpaceship& player;
};

#endif
