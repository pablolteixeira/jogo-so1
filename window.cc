#include "window.h"
#include "game.h"

sf::Texture Window::maze_tex;
sf::Sprite Window::maze_sprite;

sf::Texture Window::shot_tex;
sf::Sprite Window::shot_sprite;

sf::Texture Window::space_ship_tex;
sf::Sprite Window::space_ship_sprite;

sf::Texture Window::enemy_ship_tex;
sf::Sprite Window::enemy_ship_sprite;

void Window::draw_texture(unsigned int texture, int length, int height, float angle)
{
}

void Window::run()
{
    sf::RenderWindow window(sf::VideoMode(900, 560), "SFML works!");
    window.setKeyRepeatEnabled(false);

    Game game(window);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            game.handleEvent(event);
        }

        sf::Time elapsed = game.getElapsedTime();
        float dt = elapsed.asSeconds();

        game.restartClock();

        window.clear();

        // update and draw your objects here

        window.display();
    }
}

void Window::load_and_bind_textures()
{
    // Bind map textures    
    maze_tex.loadFromFile("sprites/maze/screen.png");
    maze_sprite.setTexture(maze_tex);
    maze_sprite.scale(1.5, 1.5);

    shot_tex.loadFromFile("sprites/space_ships/shot.png");
    shot_sprite.setTexture(shot_tex);
    shot_sprite.scale(-0.5, -0.5);

    space_ship_tex.loadFromFile("sprites/space_ships/space_ship1.png");
    space_ship_sprite.setTexture(space_ship_tex);
    space_ship_sprite.scale(-0.5, -0.5);

    enemy_ship_tex.loadFromFile("sprites/space_ships/enemy_space_ship1.png");
    enemy_ship_sprite.setTexture(enemy_ship_tex);
    enemy_ship_sprite.scale(-0.5, -0.5);
}
