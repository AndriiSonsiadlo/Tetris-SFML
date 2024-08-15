#include "Game.h"
#include "Tetromino.h"
#include <iostream>
#include <random>

namespace Tetris
{
    Game::Game(unsigned int windowSizeX, unsigned int windowSizeY, const std::string& windowTitle) :
        window(sf::VideoMode({windowSizeX, windowSizeY}), windowTitle, sf::Style::Titlebar | sf::Style::Close),
        ui(window, stats, playfield),
        state(GameState::Start)
    {
        window.setVerticalSyncEnabled(true);
        window.setFramerateLimit(60);

        initializeGame();
    }

    void Game::initializeGame()
    {
        stats = GameStats();
        playfield = Playfield();
        currentPiece = nullptr;
        nextPiece = nullptr;

        spawnNewPiece();
        spawnNewPiece();
    }

    void Game::spawnNewPiece()
    {
        static std::random_device rd;
        static std::mt19937 gen(rd());
        static std::uniform_int_distribution<> dis(0, static_cast<int>(TetrominoType::COUNT) - 1);

        if (nextPiece) {
            currentPiece = std::move(nextPiece);
            currentPiece->setPosition({4, 0});
        } else {
            auto type = static_cast<TetrominoType>(dis(gen));
            currentPiece = std::make_unique<Tetromino>(type, sf::Vector2i(4, 0));
        }

        auto nextType = static_cast<TetrominoType>(dis(gen));
        nextPiece = std::make_unique<Tetromino>(nextType, sf::Vector2i(0, 0));

        if (!playfield.canPlacePiece(currentPiece->getPositions())) {
            state = GameState::GameOver;
        }
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
        if (state == GameState::Play && currentPiece) {
            switch (key)
            {
                case sf::Keyboard::Key::A:
                case sf::Keyboard::Key::Left:
                    if (inputClock.getElapsedTime().asSeconds() > INPUT_INTERVAL) {
                        movePiece(-1, 0);
                        inputClock.restart();
                    }
                    break;
                case sf::Keyboard::Key::D:
                case sf::Keyboard::Key::Right:
                    if (inputClock.getElapsedTime().asSeconds() > INPUT_INTERVAL) {
                        movePiece(1, 0);
                        inputClock.restart();
                    }
                    break;
                case sf::Keyboard::Key::S:
                case sf::Keyboard::Key::Down:
                    dropPiece();
                    break;
                case sf::Keyboard::Key::W:
                case sf::Keyboard::Key::Up:
                    if (inputClock.getElapsedTime().asSeconds() > INPUT_INTERVAL) {
                        rotatePiece();
                        inputClock.restart();
                    }
                    break;
                case sf::Keyboard::Key::Space:
                    while (playfield.canPlacePiece(currentPiece->getPositions())) {
                        currentPiece->move(0, 1);
                    }
                    currentPiece->move(0, -1);
                    lockPiece();
                    break;
                default:
                    break;
            }
        }

        switch (key)
        {
            case sf::Keyboard::Key::Escape:
                window.close();
                break;
            case sf::Keyboard::Key::Enter:
                if (state == GameState::Start) {
                    state = GameState::Play;
                    dropClock.restart();
                }
                else if (state == GameState::GameOver) {
                    initializeGame();
                    state = GameState::Play;
                    dropClock.restart();
                }
                break;
            case sf::Keyboard::Key::P:
                if (state == GameState::Play) {
                    state = GameState::Pause;
                }
                else if (state == GameState::Pause) {
                    state = GameState::Play;
                    dropClock.restart();
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

    float Game::getDropSpeed() const
    {
        return std::max(0.1f, DROP_INTERVAL - (stats.getLevel() - 1) * 0.1f);
    }

    void Game::handleEvents()
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
            if (event->is<sf::Event::KeyPressed>())
                processKeyPress(event->getIf<sf::Event::KeyPressed>()->code);
        }
    }

    void Game::update(const sf::Time deltaTime)
    {
        if (state == GameState::Play)
        {
            stats.updateGameTime(static_cast<unsigned int>(deltaTime.asSeconds()));

            if (dropClock.getElapsedTime().asSeconds() > getDropSpeed()) {
                dropPiece();
                dropClock.restart();
            }
        }
    }

    void Game::render()
    {
        ui.clearWindow();
        ui.displayGameScreen(state, currentPiece.get(), nextPiece.get());
        ui.refreshWindow();
    }
}
