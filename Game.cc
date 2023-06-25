#include "Game.h"
#include <iostream>

// Private functions
void Game::initializeVariables()
{
    this->window = nullptr;
}

void Game::initWindow()
{
    this->videoMode.height = 560;
    this->videoMode.width = 900;
    this->window = new sf::RenderWindow(this->videoMode, "Jogo dos fugayte", sf::Style::Titlebar | sf::Style::Close);

    this->window->setFramerateLimit(144);
}

void Game::initMaze()
{
    this->maze_tex.loadFromFile("sprites/maze/screen.png");
    this->maze_sprite.setTexture(maze_tex);
    this->maze_sprite.scale(1.5, 1.5);
}

void Game::initPlayerShip()
{
    this->playerShip = new Ship();
}

// Constructors / Destructors
Game::Game() 
{   
    this->initializeVariables();
    this->initWindow();
    this->initMaze();
    this->initPlayerShip();
    //this->initEnemies();
}

Game::~Game()
{
    delete this->window;
}

// Accessors
const bool Game::running() const 
{
    return this->window->isOpen();
}

// Public functions
void Game::pollEvents()
{
     while (this->window->pollEvent(this->ev))
        {
            switch (this->ev.type) {
            case sf::Event::Closed:
                 this->window->close();
                 break;
            
            // key pressed
            case sf::Event::KeyPressed:
                sf::Keyboard::Key keyPressed = ev.key.code;

                this->playerShip->move(keyPressed);

                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                    std::cout << "Keyboard esquerda!" << std::endl;
                } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                    std::cout << "Keyboard direita!" << std::endl;
                } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                    std::cout << "Keyboard para baixo!" << std::endl;
                } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                    std::cout << "Keyboard para cima!" << std::endl;
                } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::P)) {
                    std::cout << "Keyboard P!" << std::endl;
                } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
                    std::cout << "Keyboard Q!" << std::endl;
                } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
                    std::cout << "Keyboard R!" << std::endl;
                } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
                    std::cout << "Keyboard Space!" << std::endl;
                } else
                    std::cout << "Keyboard pressed = " << ev.key.code << std::endl;
                break;
            
            }
        }
}

void Game::update()
{
    this->pollEvents();
}

void Game::render()
{   
    this->window->clear();

    // Draw game objects

    this->window->draw(maze_sprite);
    
    
    this->window->draw(this->playerShip->getShipSprite());

    /*
    space_ship_sprite.setPosition(220, 365);
    this->window->draw(space_ship_sprite);
    
    enemy_ship_sprite.setPosition(245, 150);
    this->window->draw(enemy_ship_sprite);

    shot_sprite.setPosition(204, 400);
    this->window->draw(shot_sprite);
    */

    this->window->display();
}   