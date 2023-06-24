#include "score_panel.h"

ScorePanel::ScorePanel() {
    score = 0;

    scoreText.setCharacterSize(24); 
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition(10, 10); 

    scoreText.setString("Score: 0");
}

void ScorePanel::update() {
    std::string scoreStr = std::to_string(score);
    scoreText.setString("Score: " + scoreStr);
}

void ScorePanel::addPoints(int points) {
	score += points;
}



