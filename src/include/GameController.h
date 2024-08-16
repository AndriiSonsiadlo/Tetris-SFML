#pragma once

#include <memory>
#include <random>
#include <SFML/System/Clock.hpp>

#include "Enums.h"
#include "GameStats.h"
#include "Playfield.h"
#include "Tetromino.h"

namespace Tetris
{
    class GameController
    {
    public:
        GameController();
        ~GameController() = default;

        void initializeGame();
        void updateGame(float deltaTime);
        GameState getGameState() const { return state_; }
        void setGameState(const GameState state) { state_ = state; }

        void handleLeftMove();
        void handleRightMove();
        void handleRotate();
        void handleSoftDrop();
        void handleHardDrop();
        void togglePause();
        void restartGame();
        void startGame();

        const GameStats& getStats() const { return stats_; }
        const Playfield& getPlayfield() const { return playfield_; }
        const Tetromino* getCurrentPiece() const { return currentPiece_.get(); }
        const Tetromino* getNextPiece() const { return nextPiece_.get(); }

        bool isGameOver() const;
        void resetInputDelay() { inputClock_.restart(); }

    private:
        GameState state_;
        GameStats stats_;
        Playfield playfield_;

        std::unique_ptr<Tetromino> currentPiece_;
        std::unique_ptr<Tetromino> nextPiece_;

        sf::Clock dropClock_;
        sf::Clock inputClock_;

        std::random_device rd_;
        std::mt19937 gen_;
        std::uniform_int_distribution<> dis_;

        void spawnNewPiece();
        void dropPiece();
        void movePiece(int dx, int dy);
        void rotatePiece();
        void lockPiece();
        float getDropSpeed() const;
        bool canProcessInput() const;
        TetrominoType generateRandomTetrominoType();

        static constexpr float INPUT_DELAY = 0.1f;
        static constexpr int SPAWN_X = 4;
        static constexpr int SPAWN_Y = 0;
    };
}
