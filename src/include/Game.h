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
        sf::RenderWindow window_;
        GameStats stats_;
        GameUI ui_;
        GameState state_;
        sf::Clock gameClock_;

        void handleEvents();
        void update(sf::Time deltaTime);
        void render();
        void processKeyPress(sf::Keyboard::Key key);

    public:
        Game();
        void run();
    };
}
