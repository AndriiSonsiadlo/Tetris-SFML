#include "Game.h"

#include <iostream>

namespace Tetris
{
    Game::Game() :
        window_(sf::VideoMode({600, 800}), "Tetris", sf::Style::Titlebar | sf::Style::Close),
        state_(GameState::Start),
        ui_(window_)
    {
        window_.setVerticalSyncEnabled(true);
        window_.setFramerateLimit(60);
    }

    void Game::run()
    {
        while (window_.isOpen())
        {
            handleEvents();
            update();
            render();
        }
    }

    void Game::handleEvents()
    {
        while (const std::optional event = window_.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window_.close();
            }
            if (event->is<sf::Event::KeyPressed>())
            {
                switch (const auto* keyEvent = event->getIf<sf::Event::KeyPressed>(); keyEvent->code)
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
                            state_ = GameState::Play;
                        else if (state_ == GameState::GameOver)
                            state_ = GameState::Start;
                        break;
                    case sf::Keyboard::Key::P:
                        if (state_ == GameState::Play)
                            state_ = GameState::Pause;
                        else if (state_ == GameState::Pause)
                            state_ = GameState::Play;
                        break;
                    default:
                        break;
                }
            }
        }
    }

    void Game::update()
    {
        ui_.displayGameStats(stats_);
    }

    void Game::render()
    {
        window_.clear();

        ui_.displayGameScreen(state_);

        window_.display();
    }
}
