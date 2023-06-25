#ifndef SHIP_H
#define SHIP_H

#include <SFML/Graphics.hpp>

/*
    Class that represents the Player Ship
*/
class Ship
{
private:
    //  Variables
    unsigned int lives;
    sf::Vector2f position;

    // Space ship texture
    sf::Texture space_ship_tex;
    sf::Sprite space_ship_sprite;

    // Functions

    void initialiazeShip();

public:
    // Constructors / Destructors
    Ship ();
    virtual ~Ship();

    // Accessors
    const bool alive() const;
    sf::Sprite getShipSprite();

    // Functions
    void move(sf::Keyboard::Key keyPressed);
    void shoot();
};

#endif