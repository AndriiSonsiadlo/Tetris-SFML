#include "Tetromino.h"
#include "TetrominoShape.h"

namespace Tetris
{
    Tetromino::Tetromino(const TetrominoType type, const sf::Vector2i startPos)
        : shape(type), offset(startPos), rotationState(0)
    {
        const TetrominoShape shape(type);
        updatePositions();
    }

    void Tetromino::updatePositions()
    {
        const auto coords = shape.getCoordinates();

        positions.clear();
        positions.reserve(4);

        for (const auto& coord : coords)
        {
            positions.emplace_back(coord.x + offset.x, coord.y + offset.y);
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
        std::vector<sf::Vector2i> rotated;
        rotated.reserve(4);

        const int angle = (rotationState + 1) % 4;

        for (const auto& pos : positions)
        {
            sf::Vector2i localPos = pos - offset;
            sf::Vector2i rotatedLocal;

            switch (angle)
            {
                case 1: // 90 degrees
                    rotatedLocal = sf::Vector2i(-localPos.y, localPos.x);
                    break;
                case 2: // 180 degrees
                    rotatedLocal = sf::Vector2i(-localPos.x, -localPos.y);
                    break;
                case 3: // 270 degrees
                    rotatedLocal = sf::Vector2i(localPos.y, -localPos.x);
                    break;
                default: // 0 degrees
                    rotatedLocal = localPos;
                    break;
            }

            rotated.emplace_back(rotatedLocal + offset);
        }

        return rotated;
    }

    void Tetromino::setPosition(const sf::Vector2i newOffset)
    {
        offset = newOffset;
        updatePositions();
    }
}
