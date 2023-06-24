#include "window.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include "game.h"

int main(void)
{
    sf::RenderWindow window(sf::VideoMode(900, 560), "SFML works!");
    Game game(window);
    Window game_window(game);

    game_window.run();

    return 0;
}
