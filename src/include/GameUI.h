#pragma once

#include <SFML/Graphics.hpp>
#include "Enums.h"
#include "GameStats.h"
#include "Playfield.h"
#include "TileManager.h"
#include "Tetromino.h"

namespace Tetris
{
    class GameUI
    {
    private:
        sf::Font font;
        sf::Text levelText, scoreText, linesClearedText, nextPieceText;
        sf::RectangleShape gameBoard;
        sf::RectangleShape sidePanel;
        sf::RectangleShape nextPiecePanel;
        sf::RenderWindow& window;
        GameStats& stats;
        Playfield& playfield;
        TileManager tileManager;

        std::shared_ptr<sf::Sprite> backgroundSprite{nullptr};
        std::shared_ptr<sf::Sprite> foregroundSprite{nullptr};

        void loadAssets();
        void setupPlayScreen();

        void displayLevel(unsigned int level);
        void displayScore(unsigned int score);
        void displayLines(unsigned int lines);

        void displayPlayScreen(const Tetromino* currentPiece, const Tetromino* nextPiece);
        void displayPlayfield();
        void displayCurrentPiece(const Tetromino* piece);
        void displayNextPiece(const Tetromino* piece);
        void displayMessageScreen(const std::string& textMessage, sf::Color color = sf::Color::White) const;
        void displayGameStats();

    public:
        explicit GameUI(sf::RenderWindow& window, GameStats& stats, Playfield& playfield);


        void clearWindow() const;
        void refreshWindow() const;
        void displayGameScreen(GameState state, const Tetromino* currentPiece = nullptr,
                               const Tetromino* nextPiece                     = nullptr);
    };
}
