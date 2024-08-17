#include <iostream>
#include <random>

#include "Game.h"
#include "GameConfig.h"

namespace Tetris
{
    Game::Game() :
        window_(sf::VideoMode({GameConfig::WINDOW_WIDTH, GameConfig::WINDOW_HEIGHT}), "Tetris",
                sf::Style::Titlebar | sf::Style::Close)
        , controller_(std::make_unique<GameController>())
        , inputHandler_(std::make_unique<InputHandler>(*controller_, window_))
        , renderer_(std::make_unique<UIRenderer>(window_))
    {
        window_.setVerticalSyncEnabled(true);
        window_.setFramerateLimit(60);

        renderer_->initialize();
    }


    void Game::run()
    {
        sf::Clock clock;
        while (window_.isOpen())
        {
            const float deltaTime = clock.restart().asSeconds();
            handleEvents();
            controller_->updateGame(deltaTime);
            render();
        }
    }

    void Game::handleEvents()
    {
        while (const std::optional event = window_.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window_.close();
            inputHandler_->processEvent(event);
        }
    }

    void Game::render() const
    {
        renderer_->clear();
        renderer_->render(*controller_);
        renderer_->display();
    }
}
