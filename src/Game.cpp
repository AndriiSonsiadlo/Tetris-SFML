#include "Game.h"
#include "Tetromino.h"
#include <iostream>
#include <random>

namespace Tetris
{
    Game::Game(unsigned int windowSizeX, unsigned int windowSizeY, const std::string& windowTitle) :
        window(sf::VideoMode({windowSizeX, windowSizeY}), windowTitle, sf::Style::Titlebar | sf::Style::Close),
        ui(window, stats),
        state(GameState::Start)
    {
        window.setVerticalSyncEnabled(true);
        window.setFramerateLimit(60);
    }

    void Game::run()
    {
        sf::Clock clock;
        while (window.isOpen())
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
            case sf::Keyboard::Key::A:
            case sf::Keyboard::Key::Left:
                break;
            case sf::Keyboard::Key::D:
            case sf::Keyboard::Key::Right:
                break;
            case sf::Keyboard::Key::S:
            case sf::Keyboard::Key::Down:
                break;
            case sf::Keyboard::Key::W:
            case sf::Keyboard::Key::Up:
                break;
            case sf::Keyboard::Key::Escape:
                window.close();
                break;
            case sf::Keyboard::Key::Enter:
                if (state == GameState::Start)
                {
                    state = GameState::Play;
                }
                else if (state == GameState::GameOver)
                {
                    state = GameState::Start;
                }
                break;
            case sf::Keyboard::Key::P:
                if (state == GameState::Play)
                {
                    state = GameState::Pause;
                }
                else if (state == GameState::Pause)
                {
                    state = GameState::Play;
                }
                break;
            default:
                break;
        }
    }

    void Game::movePiece(int dx, int dy)
    {
        if (!currentPiece) return;

        auto testPiece = *currentPiece;
        testPiece.move(dx, dy);

        if (playfield.canPlacePiece(testPiece.getPositions())) {
            currentPiece->move(dx, dy);
        }
    }

    void Game::rotatePiece() const
    {
        if (!currentPiece) return;

        if (const auto rotatedPositions = currentPiece->getRotatedPositions(); playfield.canPlacePiece(rotatedPositions)) {
            currentPiece->rotate();
        }
    }

    void Game::dropPiece()
    {
        if (!currentPiece) return;

        auto testPiece = *currentPiece;
        testPiece.move(0, 1);

        if (playfield.canPlacePiece(testPiece.getPositions())) {
            currentPiece->move(0, 1);
        } else {
            lockPiece();
        }
    }

    void Game::lockPiece()
    {
        if (!currentPiece) return;

        playfield.placePiece(currentPiece->getPositions(), currentPiece->getColor());

        if (const int linesCleared = playfield.checkAndClearLines(); linesCleared > 0) {
            stats.processLinesCleared(linesCleared);
        }

        spawnNewPiece();
        dropClock.restart();
    }
    void Game::handleEvents()
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
            if (event->is<sf::Event::KeyPressed>())
            {
                const auto* keyEvent = event->getIf<sf::Event::KeyPressed>();
                processKeyPress(keyEvent->code);
            }
        }
    }

    void Game::update(const sf::Time deltaTime)
    {
        if (state == GameState::Play)
        {
            stats.updateGameTime(static_cast<unsigned int>(deltaTime.asSeconds()));
        }
    }

    void Game::render()
    {
        ui.clearWindow();

        ui.displayGameScreen(state);

        ui.refreshWindow();
    }
}
