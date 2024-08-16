#pragma once

namespace Tetris
{
    enum class GameState
    {
        Start,
        Play,
        Pause,
        GameOver,
    };

    enum class MoveDirection
    {
        Left  = (-1, 0),
        Right = (1, 0),
        Down  = (0, 1)
    };

    enum class TetrominoType
    {
        I     = 0,
        Z     = 1,
        S     = 2,
        T     = 3,
        L     = 4,
        J     = 5,
        O     = 6,
        COUNT = 7
    };

    enum class TileDirection
    {
        UP    = 0,
        RIGHT = 1,
        DOWN  = 2,
        LEFT  = 3
    };

    enum class TileColor
    {
        CYAN        = 0,
        BLUE        = 1,
        PURPLE      = 2,
        PINK        = 3,
        LIGHT_GREEN = 4,
        YELLOW      = 5,
        RED         = 6,
        GREEN       = 7,
        COUNT       = 8
    };
}
