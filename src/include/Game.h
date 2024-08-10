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
        GameBackground background_;
        GameStats stats_;
        GameUI ui_;
        GameState state_;

        void handleEvents();
        void update();
        void render();

    public:
        Game();
        void run();
    };
}
