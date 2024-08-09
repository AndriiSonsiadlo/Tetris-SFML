#include "TetrominoManager.h"

#include "TetrominoShape.h"

namespace Tetris
{
    TetrominoManager::TetrominoManager(TileManager& tileManager)
        : tileManager(tileManager)
    {
    }

    std::vector<sf::Sprite> TetrominoManager::createTetrominoSprites(
        const TetrominoConstants::TetrominoType type) const
    {
        std::vector<sf::Sprite> sprites;
        sprites.reserve(4);

        const TetrominoShape shape(type);

        const auto color = shape.getColor();

        for (const auto coordinates = shape.getCoordinates(); const auto coordinate : coordinates)
        {
            auto sprite = tileManager.createSprite(color);
            sprite.setPosition({
                static_cast<float>(coordinate.x * TileConstants::TILE_SIZE),
                static_cast<float>(coordinate.y * TileConstants::TILE_SIZE)
            });
            sprites.push_back(sprite);
        }
        return sprites;
    }
}
