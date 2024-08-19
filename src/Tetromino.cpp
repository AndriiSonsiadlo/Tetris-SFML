#include "Tetromino.h"
#include "TetrominoShape.h"

namespace Tetris
{
    Tetromino::Tetromino(const TetrominoType type, const sf::Vector2i startPos)
        : shape(type), offset(startPos), rotationState(0)
    {
        updatePositions();
    }

    void Tetromino::updatePositions()
    {
        const auto coords = shape.getCoordinates();
        positions.clear();
        positions.reserve(4);

        for (const auto& coord : coords)
        {
            const sf::Vector2i rotatedCoord = rotatePoint(coord.x, coord.y, rotationState);
            positions.emplace_back(rotatedCoord.x + offset.x, rotatedCoord.y + offset.y);
        }
    }

    sf::Vector2i Tetromino::rotatePoint(int x, int y, const int rotation) const
    {
        if (shape.getType() == TetrominoType::O)
            return {x, y};

        switch (rotation % 4)
        {
            case 0: return {x, y};   // 0 degrees
            case 1: return {-y, x};  // 90 degrees
            case 2: return {-x, -y}; // 180 degrees
            case 3: return {y, -x};  // 270 degrees
            default: return {x, y};
        }
    }

    void Tetromino::move(const int dx, const int dy)
    {
        offset.x += dx;
        offset.y += dy;
        updatePositions();
    }

    void Tetromino::rotate()
    {
        rotationState = (rotationState + 1) % 4;
        updatePositions();
    }

    std::vector<sf::Vector2i> Tetromino::getRotatedPositions() const
    {
        std::vector<sf::Vector2i> rotatedPositions;
        rotatedPositions.reserve(4);

        const auto coords      = shape.getCoordinates();
        const int nextRotation = (rotationState + 1) % 4;

        for (const auto& coord : coords)
        {
            const sf::Vector2i rotatedCoord = rotatePoint(coord.x, coord.y, nextRotation);
            rotatedPositions.emplace_back(rotatedCoord.x + offset.x, rotatedCoord.y + offset.y);
        }

        return rotatedPositions;
    }

    void Tetromino::setPosition(const sf::Vector2i newOffset)
    {
        offset = newOffset;
        updatePositions();
    }
}
