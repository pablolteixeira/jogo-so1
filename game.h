#ifndef game_h
#define game_h

class PlayerSpaceship;

#include "input.h"
#include <memory>

#include <SFML/Graphics.hpp>

// Game.h
class Game {
public:
    Game(sf::RenderWindow& windown);
	~Game();

	void handleEvent(const sf::Event& event);
    sf::Time getElapsedTime() const;
    void restartClock();    
	void run();

private:
    sf::RenderWindow& window;
	sf::Clock *clock;
    std::unique_ptr<PlayerSpaceship> player;
    std::unique_ptr<Input> input;
};


#endif

