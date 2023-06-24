
#include "spaceship.h"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>
#include "shot.h"

void Spaceship::fire() {
	sf::FloatRect spriteSize = sprite.getGlobalBounds();
	sf::Vector2f position = sprite.getPosition();
	Shot *shot = nullptr;

	switch (direction) {
		case Direction::BACKWARDS:
			shot = new Shot(position.x + spriteSize.width/2.0, position.y + spriteSize.height);
			break;
		case Direction::FORWARDS:
			shot = new Shot(position.x + spriteSize.width/2.0, position.y);
			break;
		case Direction::LEFT:
			shot = new Shot(position.x, position.y + spriteSize.height/2.0f);
			break;
		case Direction::RIGHT:
			shot = new Shot(position.x + spriteSize.width, position.y + spriteSize.height/2.0f);
			break;
	}
	shot->owner = this;
			
	//Shot::queue_mutex.p();
	Shot::getActiveShots().push_back(shot);
	//Shot::queue_mutex.v();
}
