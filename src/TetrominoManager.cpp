#include "include/TetrominoManager.h"


TetrominoManager::TetrominoManager(TileManager& tileManager)
    : tileManager(tileManager)
{
}

std::vector<sf::Sprite> TetrominoManager::createTetrominoSprites(
    const Tetris::TetrominoConstants::TetrominoType type) const
{
    std::vector<sf::Sprite> sprites;
    sprites.reserve(4);

    const auto color = getTetrominoColor(type);
    const auto coordinates = Tetris::TetrominoConstants::getTetrominoCoordinates(type);

    for (int i = 0; i < 4; ++i)
    {
        auto sprite = tileManager.createSprite(color);
        sprite.setPosition({
            static_cast<float>(coordinates[i][0] * Tetris::TileConstants::TILE_SIZE),
            static_cast<float>(coordinates[i][1] * Tetris::TileConstants::TILE_SIZE)
        });
        sprites.push_back(sprite);
    }
    return sprites;
}

Tetris::TileConstants::TileColor TetrominoManager::getTetrominoColor(
    Tetris::TetrominoConstants::TetrominoType type)
{
    return Tetris::TetrominoConstants::TETROMINO_COLORS[static_cast<int>(type)];
}
