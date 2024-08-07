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

    constexpr std::array TETROMINO_COLORS = {
        TileConstants::TileColor::CYAN,    // I
        TileConstants::TileColor::RED,     // Z
        TileConstants::TileColor::GREEN,   // S
        TileConstants::TileColor::PURPLE,  // T
        TileConstants::TileColor::BLUE,    // L
        TileConstants::TileColor::PINK,    // J
        TileConstants::TileColor::YELLOW   // O
    };

    inline std::array<int, 4> getTetrominoShape(TetrominoType type)
    {
        const int shapeType = static_cast<int>(type);

        return std::array<int, 4>{
            TETROMINO_SHAPES[shapeType][0],
            TETROMINO_SHAPES[shapeType][1],
            TETROMINO_SHAPES[shapeType][2],
            TETROMINO_SHAPES[shapeType][3]
        };
    }

    inline std::array<int[2], 4> getTetrominoCoordinates(const TetrominoType type)
    {
        const auto shape = getTetrominoShape(type);
        std::array<int[2], 4> coordinates;

        for (int i = 0; i < 4; ++i)
        {
            const int offsetX = (shape[i] % 2);
            const int offsetY = (shape[i] / 2);
            coordinates[i][0] = offsetX;
            coordinates[i][1] = offsetY;
        }

        return coordinates;
    }
}
