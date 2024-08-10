#pragma once

#include <SFML/Graphics.hpp>

namespace Tetris
{
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
        void updateLevel(unsigned int level);
        void updateScore(unsigned int score);
        void updateLines(unsigned int lines);
    };
}
