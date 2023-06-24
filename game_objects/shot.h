#ifndef shot_h
#define shot_h

#include "game_object.h"
#include "spaceship.h"
#include "../thread/traits.h"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Vector2.hpp>
#include "semaphore.h"

class Shot : public GameObject {
public:
    Shot(int pos_x, int pos_y) {
		sf::Sprite sprite;
		sf::Texture texture;
		texture.loadFromFile("TODO: this");
		sprite.setTexture(texture);	
		sprite.setPosition(sf::Vector2f(pos_x, pos_y));
	};

	bool isAlive = true;
	void run(); 
	static std::vector<Shot*> getActiveShots() { return active_shots; } ;
	//static SOLUTION::Semaphore queue_mutex; 
	void die() override;
	Spaceship *owner;
   
private:
	void move();
	std::tuple<bool, GameObject*> detectHit();
	std::vector<Shot> shots;
	static std::vector<Shot*> active_shots;
};

#endif
