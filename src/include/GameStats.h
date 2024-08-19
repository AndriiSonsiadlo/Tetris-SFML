#pragma once

namespace Tetris
{
    class GameStats
    {
    public:
        enum class ScoreMultiplier
        {
            SINGLE_LINE  = 40,
            DOUBLE_LINES = 100,
            TRIPLE_LINES = 300,
            TETRIS       = 1200
        };

        static constexpr unsigned int LINES_PER_LEVEL = 10;
        static constexpr unsigned int LEVEL_THRESHOLD = 4;

    private:
        unsigned int level_{1};
        unsigned int score_{0};
        unsigned int linesCleared_{0};
        float gameTime_{0.0f}; // in seconds

        void updateScore(unsigned int lines);
        void checkLevelUp(unsigned int oldLines);

    public:
        GameStats() = default;

        [[nodiscard]] unsigned int getScore() const { return score_; }
        [[nodiscard]] unsigned int getLevel() const { return level_; }
        [[nodiscard]] unsigned int getLinesCleared() const { return linesCleared_; }
        [[nodiscard]] unsigned int getGameTimeSeconds() const { return static_cast<unsigned int>(gameTime_); }

        void updateGameTime(const float deltaTime) { gameTime_ += deltaTime; }
        void processLinesCleared(unsigned int lineCount);
    };
}
