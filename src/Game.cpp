#include "Game.h"

namespace Tetris
{
    Game::Game() :
        window_(sf::VideoMode({700, 700}), "Space Puzzle Game"),
        background_("../assets/background.jpg", "../assets/foreground.jpg")
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
