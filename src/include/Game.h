#pragma once

#include <SFML/Graphics.hpp>
#include "GameBackground.h"
#include "GameStats.h"
#include "GameUI.h"
#include "GameStates.h"

namespace Tetris
{
    class Game
    {
    private:
        sf::RenderWindow window;
        GameStats stats;
        GameUI ui;
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
