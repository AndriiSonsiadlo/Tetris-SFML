#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include "GameBackground.h"
#include "GameStats.h"
#include "GameUI.h"
#include "GameStates.h"
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
        TileManager tileManager;
        GameUI ui;
        Playfield playfield;
        std::unique_ptr<Tetromino> currentPiece;
        std::unique_ptr<Tetromino> nextPiece;
        GameState state;

        void handleEvents();
        void update(sf::Time deltaTime);
        void render();
        void processKeyPress(sf::Keyboard::Key key);

    public:
        Game(unsigned int windowSizeX, unsigned int windowSizeY, std::string windowTitle);
        void run();
    };
}
