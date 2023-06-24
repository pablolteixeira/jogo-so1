#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

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

    // Maze Texture
    sf::Texture maze_tex;
    sf::Sprite maze_sprite;
    
    //Shot texture
    sf::Texture shot_tex;
    sf::Sprite shot_sprite;
    
    //Space ship texture
    sf::Texture space_ship_tex;
    sf::Sprite space_ship_sprite;

    //Enemy space ship texture
    sf::Texture enemy_ship_tex;
    sf::Sprite enemy_ship_sprite;

    /*
        Private functions
    */

    void initializeVariables();
    void initWindow();
    void initEnemies();

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