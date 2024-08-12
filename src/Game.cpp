#include "Game.h"

#include <iostream>

namespace Tetris
{
    Game::Game() :
        window_(sf::VideoMode({600, 800}), "Tetris", sf::Style::Titlebar | sf::Style::Close),
        state_(GameState::Start),
        ui_(window_, stats_)
    {
        window_.setVerticalSyncEnabled(true);
        window_.setFramerateLimit(60);
    }

    void Game::run()
    {
        sf::Clock clock;
        while (window_.isOpen())
        {
            const sf::Time deltaTime = clock.restart();
            handleEvents();
            update(deltaTime);
            render();
        }
    }

    void Game::processKeyPress(const sf::Keyboard::Key key)
    {
        switch (key)
        {
            case sf::Keyboard::Key::Left:
                std::cout << "Left key pressed" << std::endl;
                break;
            case sf::Keyboard::Key::Right:
                std::cout << "Right key pressed" << std::endl;
                break;
            case sf::Keyboard::Key::Down:
                std::cout << "Down key pressed" << std::endl;
                break;
            case sf::Keyboard::Key::Up:
                std::cout << "Up key pressed" << std::endl;
                break;
            case sf::Keyboard::Key::Escape:
                window_.close();
                break;
            case sf::Keyboard::Key::Enter:
                if (state_ == GameState::Start)
                {
                    state_ = GameState::Play;
                }
                else if (state_ == GameState::GameOver)
                {
                    state_ = GameState::Start;
                }
                break;
            case sf::Keyboard::Key::P:
                if (state_ == GameState::Play)
                {
                    state_ = GameState::Pause;
                }
                else if (state_ == GameState::Pause)
                {
                    state_ = GameState::Play;
                }
                break;
            default:
                break;
        }
    }

    void Game::handleEvents()
    {
        while (const std::optional event = window_.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window_.close();
            if (event->is<sf::Event::KeyPressed>())
            {
                const auto* keyEvent = event->getIf<sf::Event::KeyPressed>();
                processKeyPress(keyEvent->code);
            }
        }
    }

    void Game::update(const sf::Time deltaTime)
    {
        if (state_ == GameState::Play)
        {
            stats_.updateGameTime(static_cast<unsigned int>(deltaTime.asSeconds()));
        }
    }

    void Game::render()
    {
        ui_.clearWindow();

        ui_.displayGameScreen(state_);

        ui_.refreshWindow();
    }
}
