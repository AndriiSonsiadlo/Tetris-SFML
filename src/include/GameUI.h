#pragma once

#include <SFML/Graphics.hpp>

class GameUI
{
private:
    sf::Font font;
    sf::Text levelText, scoreText, linesClearedText;
    sf::RectangleShape gameBoard;
    sf::RectangleShape sidePanel;

public:
    GameUI();
    void setupUI();
    void updateLevel(int level);
    void updateScore(int score);
    void updateLines(int lines);
};
