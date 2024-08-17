#pragma once

#include <SFML/Graphics.hpp>
#include <memory>

#include "GameController.h"
#include "InputHandler.h"
#include "UIRenderer.h"

namespace Tetris
{
    class Game
    {
    public:
        Game();
        ~Game() = default;

        void run();

    private:
        sf::RenderWindow window_;
        std::unique_ptr<GameController> controller_;
        std::unique_ptr<InputHandler> inputHandler_;
        std::unique_ptr<UIRenderer> renderer_;

        void handleEvents();
        void render() const;
    };
}
