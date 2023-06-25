#ifndef SHOT_H
#define SHOT_H

#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include "enums/direction.h"
#include "enums/ship_type.h"

class Shot {
public:
    Shot(float startX, float startY, Direction direction, ShipType shipType, float speed);
    ~Shot();
    static void updateShots(float dt);
    static void renderShots(sf::RenderWindow& window);
	void die();
    
    sf::Sprite sprite;
    static std::vector<Shot*> _shots;
    ShipType ship_type;

private:
    void update(float dt);
    void render(sf::RenderWindow& window);
	void move(float dt);

    //  Variables
    sf::Vector2f position;
    sf::Texture texture;
    float speed;
    Direction direction;
	sf::Vector2f directionVector;
};

#endif
