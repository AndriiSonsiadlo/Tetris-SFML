#include <iostream>

#include "include/TileManager.h"


TileManager::TileManager()
{
}

bool TileManager::loadTileTexture(const std::string& filename)
{
    if (!tileTexture.loadFromFile(filename))
    {
        std::cerr << "Error loading tile texture: " << filename << std::endl;
        return false;
    }
    return true;
}

const sf::Texture& TileManager::getTexture() const
{
    return tileTexture;
}


sf::IntRect TileManager::getTileRect(Tetris::TileConstants::TileColor color)
{
    const int tileIndex = static_cast<int>(color);
    return Tetris::TileConstants::TILE_RECTS[tileIndex];
}

void TileManager::setSpriteTile(sf::Sprite& sprite, const Tetris::TileConstants::TileColor color) const
{
    sprite.setTexture(tileTexture);
    sprite.setTextureRect(getTileRect(color));
}

sf::Sprite TileManager::createSprite(const Tetris::TileConstants::TileColor color) const
{
    return sf::Sprite(tileTexture, getTileRect(color));
}
