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

        void setupPlayScreen();

        void displayLevel(unsigned int level);
        void displayScore(unsigned int score);
        void displayLines(unsigned int lines);

        void displayPlayScreen() const;
        void displayMessageScreen(const std::string& textMessage, sf::Color color = sf::Color::White) const;
    public:
        explicit GameUI(sf::RenderWindow& window);

        void refreshWindow() const;

        void displayGameStats(const GameStats& stats);
        void displayGameScreen(GameState state) const;
    };
}
