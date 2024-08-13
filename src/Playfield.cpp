#include "Playfield.h"
#include <algorithm>

Playfield::Playfield() {
    for (auto& row : grid) {
        std::ranges::fill(row, Cell::Empty);
    }
}

bool Playfield::isInBounds(const int x, const int y) const {
    return x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT;
}

bool Playfield::isCellEmpty(const int x, const int y) const {
    return isInBounds(x, y) && grid[y][x] == Cell::Empty;
}

void Playfield::setCell(int x, int y, Cell value) {
    if (isInBounds(x, y)) {
        grid[y][x] = value;
    }
}

Playfield::Cell Playfield::getCell(int x, int y) const {
    if (isInBounds(x, y)) {
        return grid[y][x];
    }
    return Cell::Filled; // Treat out-of-bounds as filled (prevents placing)
}

// Piece logic
bool Playfield::canPlacePiece(const std::vector<sf::Vector2i>& coords) const {
    for (const auto& pos : coords) {
        if (!isInBounds(pos.x, pos.y) || !isCellEmpty(pos.x, pos.y)) {
            return false;
        }
    }
    return true;
}

void Playfield::placePiece(const std::vector<sf::Vector2i>& coords, Cell value) {
    for (const auto& pos : coords) {
        if (isInBounds(pos.x, pos.y)) {
            grid[pos.y][pos.x] = value;
        }
    }
}

void Playfield::clearPiece(const std::vector<sf::Vector2i>& coords) {
    placePiece(coords, Cell::Empty);
}

// Line logic
bool Playfield::isLineFull(int y) const {
    for (int x = 0; x < WIDTH; ++x) {
        if (grid[y][x] == Cell::Empty)
            return false;
    }
    return true;
}

void Playfield::clearLine(int y) {
    for (int x = 0; x < WIDTH; ++x) {
        grid[y][x] = Cell::Empty;
    }
}

void Playfield::shiftDownFrom(int row) {
    for (int y = row; y > 0; --y) {
        grid[y] = grid[y - 1];
    }
    // Clear top row
    std::fill(grid[0].begin(), grid[0].end(), Cell::Empty);
}

int Playfield::checkAndClearLines() {
    int linesCleared = 0;

    for (int y = HEIGHT - 1; y >= 0; --y) {
        if (isLineFull(y)) {
            clearLine(y);
            shiftDownFrom(y);
            ++linesCleared;
            ++y;
        }
    }

    return linesCleared;
}

void Playfield::clearAllLines() {
    for (int y = 0; y < HEIGHT; ++y) {
        clearLine(y);
    }
}

bool Playfield::isGameOver() const {
    // Check if top 2 rows are occupied (assuming 2-row spawn buffer)
    for (int y = 0; y < 2; ++y) {
        for (int x = 0; x < WIDTH; ++x) {
            if (grid[y][x] != Cell::Empty)
                return true;
        }
    }
    return false;
}
