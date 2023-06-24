
#ifndef shot_panel_h
#define shot_panel_h

#include <SFML/Graphics.hpp>

class ScorePanel {
public:
    ScorePanel();
    void addPoints(int points);
    void draw(sf::RenderWindow &window);
private:
    int score;
    sf::Text scoreText;
};

#endif
