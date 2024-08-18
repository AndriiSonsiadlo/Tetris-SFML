#pragma once

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

        void move(int dx, int dy);
        void rotate();
        [[nodiscard]] std::vector<sf::Vector2i> getRotatedPositions() const;
        void setPosition(sf::Vector2i newOffset);
    };
}
