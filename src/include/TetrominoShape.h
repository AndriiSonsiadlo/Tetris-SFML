#pragma once


#include <array>
#include <vector>

#include "../const/TetrominoConstants.h"


namespace Tetris
{
    struct Point;

    using Shape = std::array<int, 4>;
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
        TetrominoConstants::TetrominoType shapeType;

        explicit TetrominoShape(const TetrominoConstants::TetrominoType type)
            : shapeType(type)
        {
        }

        Coordinates getCoordinates() const
        {
            Coordinates shapeCoordinates{};

            const auto shape = getShape();
            for (int i = 0; i < shape.size(); ++i)
            {
                const int x = (shape[i] % 2);
                const int y = (shape[i] / 2);
                shapeCoordinates[i] = {x, y};
            }
            return shapeCoordinates;
        }

        Shape getShape() const
        {
            return TetrominoConstants::TETROMINO_SHAPE_MAP[shapeType];
        }

        TileConstants::TileColor getColor() const
        {
            return TetrominoConstants::TETROMINO_COLOR_MAP[shapeType];
        }
    };
}
