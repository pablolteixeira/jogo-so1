#include "score_panel.h"
#include <iostream>
#include <sys/stat.h>

ScorePanel::ScorePanel() {
	// Load font
    if (!this->font.loadFromFile("/usr/share/fonts/gnu-free/FreeSansBold.otf")) { // Adjust the file path as necessary
        std::cout << "Failed to load font\n";
        exit(1);
    }

    // Initialize text objects
    this->playerLivesText.setFont(this->font);
    this->playerLivesText.setCharacterSize(24); // adjust the size as you like
    this->playerLivesText.setFillColor(sf::Color::White); // color
    this->playerLivesText.setPosition(600.f, 20.f); // set position near right side of the window

    this->scoreText.setFont(this->font);
    this->scoreText.setCharacterSize(24);
    this->scoreText.setFillColor(sf::Color::White);
    this->scoreText.setPosition(600.f, 60.f);

    this->velocityText.setFont(this->font);
    this->velocityText.setCharacterSize(24);
    this->velocityText.setFillColor(sf::Color::White);
    this->velocityText.setPosition(600.f, 100.f);
}

void ScorePanel::update(int playerLives, int score, int velocity) {
    playerLivesText.setString("Lives: " + std::to_string(playerLives));
    scoreText.setString("Score: " + std::to_string(score));
    velocityText.setString("Velocity: " + std::to_string(velocity));
}

void ScorePanel::render(sf::RenderWindow& window) {
    window.draw(playerLivesText);
    window.draw(scoreText);
    window.draw(velocityText);
}


