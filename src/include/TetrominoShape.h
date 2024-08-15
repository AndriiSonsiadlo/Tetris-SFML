#pragma once


#include <array>

#include "TetrominoConst.h"


namespace Tetris
{
    struct Point;

    using Shape       = std::array<int, 4>;
    using Coordinates = std::array<Point, 4>;

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
        explicit TetrominoShape(const TetrominoType type)
            : shapeType(type)
        {
        }

        [[nodiscard]] Coordinates getCoordinates() const
        {
            Coordinates shapeCoordinates{};

            const auto shape = getShape();
            for (int i = 0; i < shape.size(); ++i)
            {
                const int x         = (shape[i] % 2);
                const int y         = (shape[i] / 2);
                shapeCoordinates[i] = {x, y};
            }
            return shapeCoordinates;
        }

        [[nodiscard]] Shape getShape() const
        {
            return TetrominoConst::TETROMINO_SHAPE_MAP[shapeType];
        }

        [[nodiscard]] TileColor getColor() const
        {
            return TetrominoConst::TETROMINO_COLOR_MAP[shapeType];
        }

        [[nodiscard]] TetrominoType getType() const
        {
            return shapeType;
        }
    };
}
