#ifndef score_panel_h
#define score_panel_h

#include <SFML/Graphics.hpp>

class ScorePanel {
private:
    sf::Text playerLivesText;
    sf::Text scoreText;
    sf::Text velocityText;
    sf::Font font;
public:
    ScorePanel();

    void update(int playerLives, int score, int velocity);
    void render(sf::RenderWindow& window);
};

#endif
