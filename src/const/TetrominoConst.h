#pragma once

#include <unordered_map>
#include <array>
#include <vector>

#include "Enums.h"

namespace Tetris::TetrominoConst
{
    constexpr int TETROMINO_COUNT = static_cast<int>(TetrominoType::COUNT);

    // Tetromino shapes are represented in a 2x4 grid:
    //  [0][1]
    //  [2][3]
    //  [4][5]
    //  [6][7]

    inline std::unordered_map<TetrominoType, std::vector<std::array<int, 2>>> TETROMINO_SHAPES = {
        {TetrominoType::I, {{-1, 0}, {0, 0}, {1, 0}, {2, 0}}},   // I-piece (horizontal line)
        {TetrominoType::O, {{0, 0}, {1, 0}, {0, 1}, {1, 1}}},    // O-piece (square)
        {TetrominoType::T, {{0, 0}, {-1, 0}, {1, 0}, {0, -1}}},  // T-piece
        {TetrominoType::S, {{0, 0}, {1, 0}, {0, -1}, {-1, -1}}}, // S-piece
        {TetrominoType::Z, {{0, 0}, {-1, 0}, {0, -1}, {1, -1}}}, // Z-piece
        {TetrominoType::J, {{0, 0}, {-1, 0}, {1, 0}, {1, -1}}},  // J-piece
        {TetrominoType::L, {{0, 0}, {-1, 0}, {1, 0}, {-1, -1}}}  // L-piece
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
