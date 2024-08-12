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
        sf::RenderWindow& window;
        GameBackground background;
        GameStats& stats;

        void setupPlayScreen();

        void displayLevel(unsigned int level);
        void displayScore(unsigned int score);
        void displayLines(unsigned int lines);

        void displayPlayScreen();
        void displayMessageScreen(const std::string& textMessage, sf::Color color = sf::Color::White) const;
        void displayGameStats();
    public:
        explicit GameUI(sf::RenderWindow& window, GameStats& stats);

        void clearWindow() const;
        void refreshWindow() const;

        void displayGameScreen(GameState state);
    };
}
