#include <iostream>

#include "TileManager.h"

namespace Tetris
{
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


    sf::IntRect TileManager::getTileRect(TileColor color)
    {
        return TileConst::TILE_RECT_MAP[color];
    }

    void TileManager::setSpriteTile(sf::Sprite& sprite, const TileColor color) const
    {
        sprite.setTexture(tileTexture);
        sprite.setTextureRect(getTileRect(color));
    }

    sf::Sprite TileManager::createSprite(const TileColor color) const
    {
        return sf::Sprite(tileTexture, getTileRect(color));
    }

    void TileManager::moveRelativeTo(sf::Sprite& sourceSprite, const sf::Sprite& relateSprite,
                                     const TileDirection direction)
    {
        float tileSize;
        sf::Vector2f newPosition = relateSprite.getPosition();

        switch (direction)
        {
        case TileDirection::RIGHT:
            tileSize = sourceSprite.getGlobalBounds().size.x;
            newPosition.x += tileSize;
            break;
        case TileDirection::LEFT:
            tileSize = sourceSprite.getGlobalBounds().size.x;
            newPosition.x -= tileSize;
            break;
        case TileDirection::UP:
            tileSize = sourceSprite.getGlobalBounds().size.y;
            newPosition.y -= tileSize;
            break;
        case TileDirection::DOWN:
            tileSize = sourceSprite.getGlobalBounds().size.y;
            newPosition.y += tileSize;
            break;
        default:
            return;
        }

        sourceSprite.setPosition(newPosition);
    }
}
