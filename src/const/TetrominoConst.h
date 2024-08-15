#pragma once

#include "Enums.h"
#include "TileConst.h"

namespace Tetris::TetrominoConst
{
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

    inline std::unordered_map<TetrominoType, TileColor> TETROMINO_COLOR_MAP = {
        {TetrominoType::I, TileColor::CYAN},
        {TetrominoType::Z, TileColor::RED},
        {TetrominoType::S, TileColor::GREEN},
        {TetrominoType::T, TileColor::PURPLE},
        {TetrominoType::L, TileColor::BLUE},
        {TetrominoType::J, TileColor::PINK},
        {TetrominoType::O, TileColor::YELLOW}
    };
}
