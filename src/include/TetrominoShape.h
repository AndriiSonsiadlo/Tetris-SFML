#pragma once

#include <array>
#include <vector>

#include "TetrominoConst.h"

namespace Tetris
{
    struct Point
    {
        int x;
        int y;

        Point(const int x, const int y) : x(x), y(y)
        {
        }

        Point() : Point(0, 0)
        {
        }
    };

    struct TetrominoShape
    {
    private:
        TetrominoType shapeType;

    public:
        explicit TetrominoShape(const TetrominoType type) : shapeType(type)
        {
        }

        [[nodiscard]] std::vector<Point> getCoordinates() const
        {
            std::vector<Point> coordinates;
            const auto& shape = TetrominoConst::TETROMINO_SHAPES.at(shapeType);

            for (const auto& coord : shape)
            {
                coordinates.emplace_back(coord[0], coord[1]);
            }

            return coordinates;
        }

        [[nodiscard]] TileColor getColor() const
        {
            return TetrominoConst::TETROMINO_COLOR_MAP.at(shapeType);
        }

        [[nodiscard]] TetrominoType getType() const
        {
            return shapeType;
        }
    };
}
