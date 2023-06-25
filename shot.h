#ifndef SHOT_H
#define SHOT_H

#include <SFML/Graphics.hpp>
#include "enums/direction.h"
#include "enums/ship_type.h"

class Shot {
public:
    Shot(float startX, float startY, Direction direction, ShipType shipType);
    ~Shot();
    static void updateShots();
    static void renderShots(sf::RenderWindow& window);
    
    sf::Sprite sprite;
    static std::vector<Shot*> _shots;
private:
    void update();
    void render(sf::RenderWindow& window);

    //  Variables
    sf::Vector2f position;
    sf::Texture texture;
    float speed;
    Direction direction;
    ShipType shipType;
};

#endif