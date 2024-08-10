#include "GameStats.h"

namespace Tetris
{
    void GameStats::checkLevelUp(unsigned int oldLines)
    {
        if (linesCleared_ % LINES_PER_LEVEL < LEVEL_THRESHOLD &&
            oldLines % LINES_PER_LEVEL >= LEVEL_THRESHOLD)
        {
            level_++;
        }
    }

    void GameStats::updateScore(const unsigned int lines)
    {
        ScoreMultiplier multiplier;

        switch (lines)
        {
            case 1:
                multiplier = ScoreMultiplier::SINGLE_LINE;
                break;
            case 2:
                multiplier = ScoreMultiplier::DOUBLE_LINES;
                break;
            case 3:
                multiplier = ScoreMultiplier::TRIPLE_LINES;
                break;
            case 4:
            default:
                multiplier = ScoreMultiplier::TETRIS;
        }

        score_ += static_cast<unsigned int>(multiplier) * (level_ + 1);
    }

    void GameStats::processLinesCleared(const unsigned int lineCount)
    {
        updateScore(lineCount);
        const unsigned int oldLines = linesCleared_;
        linesCleared_ += lineCount;
        checkLevelUp(oldLines);
    }

    void GameStats::updateGameTime(const unsigned int seconds)
    {
        gameTime_ += seconds;
    }
}
