#include "include/InputHandler.h"
#include "GameController.h"

namespace Tetris
{
    InputHandler::InputHandler(GameController& controller, sf::RenderWindow& window)
        : controller_(controller), window_(window)
    {
        setupKeyBindings();
    }

    void InputHandler::handleKeyPress(const sf::Keyboard::Key key)
    {
        if (const auto it = keyBindings_.find(key); it != keyBindings_.end())
        {
            it->second();
        }
    }

    void InputHandler::processEvent(const std::optional<sf::Event>& event)
    {
        if (event->is<sf::Event::KeyPressed>())
        {
            const auto& keyEvent = event->getIf<sf::Event::KeyPressed>();
            handleKeyPress(keyEvent->code);
        }
    }

    void InputHandler::setupKeyBindings()
    {
        keyBindings_[sf::Keyboard::Key::A]    = [this]() { controller_.handleLeftMove(); };
        keyBindings_[sf::Keyboard::Key::Left] = [this]() { controller_.handleLeftMove(); };

        keyBindings_[sf::Keyboard::Key::D]     = [this]() { controller_.handleRightMove(); };
        keyBindings_[sf::Keyboard::Key::Right] = [this]() { controller_.handleRightMove(); };

        keyBindings_[sf::Keyboard::Key::S]    = [this]() { controller_.handleSoftDrop(); };
        keyBindings_[sf::Keyboard::Key::Down] = [this]() { controller_.handleSoftDrop(); };

        keyBindings_[sf::Keyboard::Key::W]  = [this]() { controller_.handleRotate(); };
        keyBindings_[sf::Keyboard::Key::Up] = [this]() { controller_.handleRotate(); };

        keyBindings_[sf::Keyboard::Key::Space] = [this]() { controller_.handleHardDrop(); };

        keyBindings_[sf::Keyboard::Key::P]     = [this]() { controller_.togglePause(); };
        keyBindings_[sf::Keyboard::Key::Enter] = [this]()
        {
            if (controller_.getGameState() == GameState::Start)
                controller_.startGame();
            else if (controller_.getGameState() == GameState::GameOver)
                controller_.restartGame();
        };
        keyBindings_[sf::Keyboard::Key::Escape] = [this]() { window_.close(); };
    }
}
