#pragma once

#include <SFML/Window/Event.hpp>
#include <functional>
#include <unordered_map>

namespace Tetris
{
    class GameController;

    class InputHandler
    {
    public:
        explicit InputHandler(GameController& controller);
        ~InputHandler() = default;

        void handleKeyPress(sf::Keyboard::Key key);
        void processEvent(const sf::Event& event);

    private:
        GameController& controller_;
        std::unordered_map<sf::Keyboard::Key, std::function<void()>> keyBindings_;

        void setupKeyBindings();
    };
}