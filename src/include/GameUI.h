#pragma once

#include <SFML/Graphics.hpp>

#include "GameBackground.h"
#include "GameStates.h"
#include "GameStats.h"

namespace Tetris
{
    class GameUI
    {
    private:
        sf::Font font;
        sf::Text levelText, scoreText, linesClearedText;
        sf::RectangleShape gameBoard;
        sf::RectangleShape sidePanel;
        GameBackground background;
        sf::RenderWindow& window;

        void setupUI();
    public:
        explicit GameUI(sf::RenderWindow& window);

        void updateLevel(unsigned int level);
        void updateScore(unsigned int score);
        void updateLines(unsigned int lines);
        void draw() const;
        void displayGameScreen(GameState state) const;
        void displayGameStats(const GameStats& stats);
    };
}
