#pragma once

#include <cfloat>
#include <SFML/Graphics.hpp>
#include <vector>

#include "TetrominoShape.h"
#include "TileConst.h"

namespace Tetris
{
    class Tetromino
    {
    private:
        TetrominoShape shape;
        std::vector<sf::Vector2i> positions;
        sf::Vector2i offset;
        int rotationState;

        void updatePositions();
        [[nodiscard]] sf::Vector2i rotatePoint(int x, int y, int rotation) const;

    public:
        Tetromino(TetrominoType type, sf::Vector2i startPos);

        [[nodiscard]] const std::vector<sf::Vector2i>& getPositions() const { return positions; }
        [[nodiscard]] TileColor getColor() const { return shape.getColor(); }
        [[nodiscard]] TetrominoType getType() const { return shape.getType(); }
        [[nodiscard]] std::vector<Point> getCoordinates() const { return shape.getCoordinates(); }

        void move(int dx, int dy);
        void rotate();
        [[nodiscard]] std::vector<sf::Vector2i> getRotatedPositions() const;
        void setPosition(sf::Vector2i newOffset);


        [[nodiscard]] sf::Vector2f getCenterPosition() const
        {
            float minX = FLT_MAX, minY = FLT_MAX;
            float maxX = -FLT_MAX, maxY = -FLT_MAX;

            for (const auto& coord : shape.getCoordinates())
            {
                minX = std::min(minX, static_cast<float>(coord.x));
                minY = std::min(minY, static_cast<float>(coord.y));
                maxX = std::max(maxX, static_cast<float>(coord.x));
                maxY = std::max(maxY, static_cast<float>(coord.y));
            }

            return sf::Vector2f({
                minX + (maxX - minX + 1) / 2.0f,
                minY + (maxY - minY + 1) / 2.0f
            });
        }
    };
}
