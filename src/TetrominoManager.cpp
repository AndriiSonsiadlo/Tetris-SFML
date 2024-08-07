#include "include/TetrominoManager.h"

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

        const auto color = getTetrominoColor(type);
        const auto coordinates = Tetris::TetrominoConstants::getTetrominoCoordinates(type);

        for (int i = 0; i < 4; ++i)
        {
            auto sprite = tileManager.createSprite(color);
            sprite.setPosition({
                static_cast<float>(coordinates[i][0] * TileConstants::TILE_SIZE),
                static_cast<float>(coordinates[i][1] * TileConstants::TILE_SIZE)
            });
            sprites.push_back(sprite);
        }
        return sprites;
    }

    TileConstants::TileColor TetrominoManager::getTetrominoColor(
        TetrominoConstants::TetrominoType type)
    {
        return TetrominoConstants::TETROMINO_COLORS[static_cast<int>(type)];
    }
}
