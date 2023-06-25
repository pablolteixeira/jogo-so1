#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include "Ship.h"

/*
    Class that acts as the game engine.
    Wrapper class.
*/

class Game 
{
private:
    // Variables
    
    /*
        Window
    */ 
    sf::RenderWindow* window;
    sf::VideoMode videoMode;
    sf::Event ev;
    

    /*
        Game objects
    */

    // Player Ship
    Ship* playerShip;
    
    // Maze Texture
    sf::Texture maze_tex;
    sf::Sprite maze_sprite;

    /*
        Private functions
    */
   
    void initializeVariables();
    void initWindow();
    void initMaze();
    void initPlayerShip();
    //void initEnemies();

public: 
    // Constructors / Destructors
    Game ();
    virtual ~Game();

    // Accessors
    const bool running() const;

    // Functions
    void pollEvents();
    void update();
    void render();
};

#endif