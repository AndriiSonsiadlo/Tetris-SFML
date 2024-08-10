#pragma once

#include <SFML/Graphics.hpp>

#include "GameBackground.h"

namespace Tetris
{
    class GameUI
    {
    private:
        sf::Font font;
        sf::Text levelText, scoreText, linesClearedText;
        sf::RectangleShape gameBoard;
        sf::RectangleShape sidePanel;
        GameBackground background_;

        void setupUI();
    public:
        GameUI();
        void updateLevel(unsigned int level);
        void updateScore(unsigned int score);
        void updateLines(unsigned int lines);
        void draw(sf::RenderWindow& window) const;
    };
}
