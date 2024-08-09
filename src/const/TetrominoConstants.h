#pragma once

#include "TileConstants.h"

namespace Tetris::TetrominoConstants
{
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

    constexpr int TETROMINO_COUNT = static_cast<int>(TetrominoType::COUNT);

    // Tetromino shapes are represented in a 2x4 grid:
    //  [0][1]
    //  [2][3]
    //  [4][5]
    //  [6][7]

    inline std::unordered_map<TetrominoType, std::array<int, 4>> TETROMINO_SHAPE_MAP = {
        {TetrominoType::I, std::array{1, 3, 5, 7}},
        {TetrominoType::Z, std::array{2, 4, 5, 7}},
        {TetrominoType::S, std::array{3, 5, 4, 6}},
        {TetrominoType::T, std::array{3, 5, 4, 7}},
        {TetrominoType::L, std::array{2, 3, 5, 7}},
        {TetrominoType::J, std::array{3, 5, 7, 6}},
        {TetrominoType::O, std::array{2, 3, 4, 5}}
    };

    inline std::unordered_map<TetrominoType, TileConstants::TileColor> TETROMINO_COLOR_MAP = {
        {TetrominoType::I, TileConstants::TileColor::CYAN},
        {TetrominoType::Z, TileConstants::TileColor::RED},
        {TetrominoType::S, TileConstants::TileColor::GREEN},
        {TetrominoType::T, TileConstants::TileColor::PURPLE},
        {TetrominoType::L, TileConstants::TileColor::BLUE},
        {TetrominoType::J, TileConstants::TileColor::PINK},
        {TetrominoType::O, TileConstants::TileColor::YELLOW}
    };
}
