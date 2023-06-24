#ifndef player_spaceship
#define player_spaceship

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Keyboard.hpp>

class PlayerSpaceship {
public:
	void handleInput(sf::Keyboard::Key key) {
        const float speed = 100.0f;  // speed in units per second

        if (key == sf::Keyboard::Up) {
            velocity.y = -speed;
        } else if (key == sf::Keyboard::Down) {
            velocity.y = speed;
        } else if (key == sf::Keyboard::Left) {
            velocity.x = -speed;
        } else if (key == sf::Keyboard::Right) {
            velocity.x = speed;
        }
		// TODO: handle player shooting
    }	

	void update(float dt) {
		sprite.move(velocity * dt);
	}

	void draw(sf::RenderWindow& window) const {
		window.draw(sprite);
	}

private:
	sf::Sprite sprite;
	sf::Vector2f velocity;
};


#endif
