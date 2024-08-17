#pragma once

#include <SFML/Graphics.hpp>

#include <functional>
#include <optional>
#include <unordered_map>

#include "GameController.h"

namespace Tetris
{
    class InputHandler
    {
    public:
        explicit InputHandler(GameController& controller, sf::RenderWindow& window);
        ~InputHandler() = default;

        void handleKeyPress(sf::Keyboard::Key key);
        void processEvent(const std::optional<sf::Event>& event);

    private:
        GameController& controller_;
        sf::RenderWindow& window_;
        std::unordered_map<sf::Keyboard::Key, std::function<void()>> keyBindings_;

        void setupKeyBindings();
    };
}
