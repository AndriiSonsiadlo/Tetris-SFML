#pragma once

namespace Tetris::TetrominoConstants
{
    constexpr int TETROMINO_COUNT = 7;

    constexpr int TETROMINO_SHAPES[7][4] = {
        {1, 3, 5, 7}, // I     [0][1]
        {2, 4, 5, 7}, // Z     [2][3]
        {3, 5, 4, 6}, // S     [4][5]
        {3, 5, 4, 7}, // T     [6][7]
        {2, 3, 5, 7}, // L
        {3, 5, 7, 6}, // J
        {2, 3, 4, 5}, // O
    };

    enum class TetrominoType
    {
        I = 0,
        Z = 1,
        S = 2,
        T = 3,
        L = 4,
        J = 5,
        O = 6
    };
}
