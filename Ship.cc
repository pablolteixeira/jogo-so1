#include "Ship.h"

// Private functions

void Ship::initialiazeShip()
{
    this->lives = 3;
    this->position.x = 100.f;
    this->position.y = 200.f;

    this->space_ship_tex.loadFromFile("sprites/space_ships/space_ship1.png");
    this->space_ship_sprite.setTexture(space_ship_tex);
    this->space_ship_sprite.scale(-0.5, -0.5);
}

// Constructors / Destructors

Ship::Ship()
{
    this->initialiazeShip();
}

Ship::~Ship()
{

}

// Accessors

const bool Ship::alive() const
{
    return this->lives == 0;
}

sf::Sprite Ship::getShipSprite()
{
    return this->space_ship_sprite;
}

// Public functions

void Ship::shoot() 
{
    Shot 
}

void Ship::move(sf::Keyboard::Key keyPressed)
{   
    switch (keyPressed)
    {
    case sf::Keyboard::Left:
        this->position.x -= 20;
        break;
    case sf::Keyboard::Right:
        this->position.x += 20;
        break;
    case sf::Keyboard::Down:
        this->position.y += 20;
        break;
    case sf::Keyboard::Up:
        this->position.y -= 20;
        break;
    default:
        break;
    }

    this->space_ship_sprite.setPosition(this->position.x, this->position.y);
}
