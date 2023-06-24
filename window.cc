#include "window.h"
#include "Game.h"

Window::Window()
{
    run();
}

void Window::draw_texture(unsigned int texture, int length, int height, float angle)
{
}

void Window::run()
{   
    Game game;

    while (game.running())
    {
        // Update
        game.update();

        // Render 
        game.render();
    }
}
