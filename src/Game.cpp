#include "Game.h"

#include <iostream>

namespace Tetris
{
    Game::Game() :
        window_(sf::VideoMode({700, 700}), "Space Puzzle Game"),
        background_("../assets/background.jpg", "../assets/foreground.jpg"),
        state_(GameState::Start)
    {
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
                    case sf::Keyboard::Key::P:
                        if (state_ == GameState::Play)
                            state_ = GameState::Pause;
                        else if (state_ == GameState::Pause)
                            state_ = GameState::Play;
                    default:
                        break;
                }
            }
        }
    }

    void Game::update()
    {
        ui_.updateLevel(stats_.getLevel());
        ui_.updateScore(stats_.getScore());
        ui_.updateLines(stats_.getLinesCleared());
    }

    void Game::render()
    {
        window_.clear();

        background_.draw(window_);

        // ui_.draw(window);

        window_.display();
    }
}
