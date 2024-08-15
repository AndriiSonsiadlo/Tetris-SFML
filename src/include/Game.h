#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include "Enums.h"
#include "GameStats.h"
#include "GameUI.h"
#include "Playfield.h"
#include "TileManager.h"
#include "Tetromino.h"

namespace Tetris
{
    class Game
    {
    private:
        sf::RenderWindow window;
        GameStats stats;
        GameUI ui;
        Playfield playfield;
        std::unique_ptr<Tetromino> currentPiece;
        std::unique_ptr<Tetromino> nextPiece;
        GameState state;

        sf::Clock dropClock;
        sf::Clock inputClock;
        static constexpr float DROP_INTERVAL  = 1.0f;
        static constexpr float INPUT_INTERVAL = 0.1f;

        void handleEvents();
        void update(sf::Time deltaTime);
        void render();
        void processKeyPress(sf::Keyboard::Key key);

        void initializeGame();
        void spawnNewPiece();
        void dropPiece();
        void movePiece(int dx, int dy);
        void rotatePiece() const;
        void lockPiece();
        float getDropSpeed() const;

    public:
        Game(unsigned int windowSizeX, unsigned int windowSizeY, const std::string& windowTitle);
        void run();
    };
}
