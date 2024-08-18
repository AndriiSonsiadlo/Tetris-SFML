#include "Playfield.h"
#include <algorithm>

namespace Tetris
{
    Playfield::Playfield()
    {
        for (auto& row : grid)
        {
            std::ranges::fill(row, Cell::Empty);
        }
        for (auto& row : colors)
        {
            std::ranges::fill(row, TileColor::CYAN);
        }
    }

    bool Playfield::isInBounds(const int x, const int y)
    {
        return x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT;
    }

    bool Playfield::isCellEmpty(const int x, const int y) const
    {
        return isInBounds(x, y) && grid[y][x] == Cell::Empty;
    }

    void Playfield::setCell(int x, int y, Cell value, TileColor color)
    {
        if (isInBounds(x, y))
        {
            grid[y][x]   = value;
            colors[y][x] = color;
        }
    }

    Playfield::Cell Playfield::getCell(int x, int y) const
    {
        if (isInBounds(x, y))
        {
            return grid[y][x];
        }
        return Cell::Filled;
    }

    TileColor Playfield::getCellColor(int x, int y) const
    {
        if (isInBounds(x, y))
        {
            return colors[y][x];
        }
        return TileColor::CYAN;
    }

    bool Playfield::canPlacePiece(const std::vector<sf::Vector2i>& coords) const
    {
        for (const auto& pos : coords)
        {
            if (!isInBounds(pos.x, pos.y) || !isCellEmpty(pos.x, pos.y))
            {
                return false;
            }
        }
        return true;
    }

    void Playfield::placePiece(const std::vector<sf::Vector2i>& coords, TileColor color)
    {
        for (const auto& pos : coords)
        {
            setCell(pos.x, pos.y, Cell::Filled, color);
        }
    }

    void Playfield::clearPiece(const std::vector<sf::Vector2i>& coords)
    {
        for (const auto& pos : coords)
        {
            setCell(pos.x, pos.y, Cell::Empty);
        }
    }

    bool Playfield::isLineFull(int y) const
    {
        for (int x = 0; x < WIDTH; ++x)
        {
            if (grid[y][x] == Cell::Empty)
                return false;
        }
        return true;
    }

    void Playfield::clearLine(int y)
    {
        for (int x = 0; x < WIDTH; ++x)
        {
            grid[y][x] = Cell::Empty;
        }
    }

    void Playfield::shiftDownFrom(int row)
    {
        for (int y = row; y > 0; --y)
        {
            grid[y]   = grid[y - 1];
            colors[y] = colors[y - 1];
        }
        std::ranges::fill(grid[0], Cell::Empty);
        std::ranges::fill(colors[0], TileColor::CYAN);
    }

    int Playfield::checkAndClearLines()
    {
        int linesCleared = 0;

        for (int y = HEIGHT - 1; y >= 0; --y)
        {
            if (isLineFull(y))
            {
                clearLine(y);
                shiftDownFrom(y);
                ++linesCleared;
                ++y;
            }
        }

        return linesCleared;
    }

    void Playfield::clearAllLines()
    {
        for (int y = 0; y < HEIGHT; ++y)
        {
            clearLine(y);
        }
    }

    bool Playfield::isGameOver() const
    {
        for (int y = 0; y < 2; ++y)
        {
            for (int x = 0; x < WIDTH; ++x)
            {
                if (grid[y][x] == Cell::Filled)
                    return true;
            }
        }
        return false;
    }
}
