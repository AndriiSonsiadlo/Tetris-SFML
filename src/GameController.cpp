#include "GameController.h"
#include "GameConfig.h"

namespace Tetris
{
    GameController::GameController()
        : state_(GameState::Start)
          , gen_(rd_())
          , dis_(0, static_cast<int>(TetrominoType::COUNT) - 1)
    {
        initializeGame();
    }

    void GameController::initializeGame()
    {
        stats_        = GameStats();
        playfield_    = Playfield();
        currentPiece_ = nullptr;
        nextPiece_    = nullptr;

        spawnNewPiece();
    }

    void GameController::updateGame(const float deltaTime)
    {
        if (state_ != GameState::Play)
            return;

        stats_.updateGameTime(static_cast<unsigned int>(deltaTime));

        if (dropClock_.getElapsedTime().asSeconds() >= getDropSpeed())
        {
            dropPiece();
            dropClock_.restart();
        }
    }

    void GameController::handleLeftMove()
    {
        if (state_ == GameState::Play && canProcessInput())
        {
            movePiece(-1, 0);
            resetInputDelay();
        }
    }

    void GameController::handleRightMove()
    {
        if (state_ == GameState::Play && canProcessInput())
        {
            movePiece(1, 0);
            resetInputDelay();
        }
    }

    void GameController::handleRotate()
    {
        if (state_ == GameState::Play && canProcessInput())
        {
            rotatePiece();
            resetInputDelay();
        }
    }

    void GameController::handleSoftDrop()
    {
        if (state_ == GameState::Play)
        {
            dropPiece();
        }
    }

    void GameController::handleHardDrop()
    {
        if (state_ == GameState::Play && currentPiece_)
        {
            while (playfield_.canPlacePiece(currentPiece_->getPositions()))
            {
                currentPiece_->move(0, 1);
            }
            currentPiece_->move(0, -1);
            lockPiece();
        }
    }

    void GameController::togglePause()
    {
        if (state_ == GameState::Play)
        {
            state_ = GameState::Pause;
        }
        else if (state_ == GameState::Pause)
        {
            state_ = GameState::Play;
            dropClock_.restart();
        }
    }

    void GameController::restartGame()
    {
        if (state_ == GameState::GameOver)
        {
            initializeGame();
            state_ = GameState::Play;
            dropClock_.restart();
        }
    }

    void GameController::startGame()
    {
        if (state_ == GameState::Start)
        {
            state_ = GameState::Play;
            dropClock_.restart();
        }
    }

    bool GameController::isGameOver() const
    {
        return state_ == GameState::GameOver;
    }

    void GameController::spawnNewPiece()
    {
        if (nextPiece_)
        {
            currentPiece_ = std::move(nextPiece_);
            currentPiece_->setPosition({SPAWN_X, SPAWN_Y});
        }
        else
        {
            auto type     = generateRandomTetrominoType();
            currentPiece_ = std::make_unique<Tetromino>(type, sf::Vector2i(SPAWN_X, SPAWN_Y));
        }

        auto nextType = generateRandomTetrominoType();
        nextPiece_    = std::make_unique<Tetromino>(nextType, sf::Vector2i(0, 0));

        if (!playfield_.canPlacePiece(currentPiece_->getPositions()))
        {
            state_ = GameState::GameOver;
        }
    }

    void GameController::dropPiece()
    {
        if (!currentPiece_)
            return;

        auto testPiece = *currentPiece_;
        testPiece.move(0, 1);

        if (playfield_.canPlacePiece(testPiece.getPositions()))
        {
            currentPiece_->move(0, 1);
        }
        else
        {
            lockPiece();
        }
    }

    void GameController::movePiece(int dx, int dy)
    {
        if (!currentPiece_)
            return;

        auto testPiece = *currentPiece_;
        testPiece.move(dx, dy);

        if (playfield_.canPlacePiece(testPiece.getPositions()))
        {
            currentPiece_->move(dx, dy);
        }
    }

    void GameController::rotatePiece()
    {
        if (!currentPiece_)
            return;

        if (const auto rotatedPositions = currentPiece_->getRotatedPositions();
            playfield_.canPlacePiece(rotatedPositions))
        {
            currentPiece_->rotate();
        }
    }

    void GameController::lockPiece()
    {
        if (!currentPiece_)
            return;

        playfield_.placePiece(currentPiece_->getPositions(), currentPiece_->getColor());

        if (const int linesCleared = playfield_.checkAndClearLines(); linesCleared > 0)
        {
            stats_.processLinesCleared(linesCleared);
        }

        spawnNewPiece();
        dropClock_.restart();
    }

    float GameController::getDropSpeed() const
    {
        return std::max(0.1f, GameConfig::DROP_INTERVAL - (stats_.getLevel() - 1) * 0.1f);
    }

    bool GameController::canProcessInput() const
    {
        return inputClock_.getElapsedTime().asSeconds() > INPUT_DELAY;
    }

    TetrominoType GameController::generateRandomTetrominoType()
    {
        return static_cast<TetrominoType>(dis_(gen_));
    }
}
