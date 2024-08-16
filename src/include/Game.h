#pragma once

#include <SFML/Graphics.hpp>
#include <memory>

#include "Enums.h"
#include "GameStats.h"
#include "GameUI.h"
#include "Playfield.h"
#include "Tetromino.h"

namespace Tetris
{
    class Game
    {
    private:
        sf::RenderWindow window;
        GameUI ui;

        GameStats stats;
        GameState state;
        Playfield playfield;

        std::unique_ptr<Tetromino> currentPiece;
        std::unique_ptr<Tetromino> nextPiece;

        sf::Clock dropClock;
        sf::Clock inputClock;

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
        Game();
        void run();
    };
}
