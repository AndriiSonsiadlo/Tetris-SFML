#pragma once

#include <SFML/Graphics.hpp>
#include "GameBackground.h"
#include "GameStats.h"
#include "GameUI.h"

namespace Tetris
{
    class Game
    {
    private:
        sf::RenderWindow window_;
        Tetris::GameBackground background_;
        Tetris::GameStats stats_;
        Tetris::GameUI ui_;

        void handleEvents();
        void update();
        void render();

    public:
        Game();
        void run();
    };
}
