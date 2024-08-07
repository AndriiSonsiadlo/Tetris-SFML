#pragma once

#include <SFML/Graphics.hpp>
#include <string>

#include "../const/TileConstants.h"

namespace Tetris
{
    class TileManager
    {
    private:
        sf::Texture tileTexture;

    public:
        TileManager();

        bool loadTileTexture(const std::string& filename);

        const sf::Texture& getTexture() const;

        static sf::IntRect getTileRect(TileConstants::TileColor color);

        void setSpriteTile(sf::Sprite& sprite, TileConstants::TileColor color) const;

        sf::Sprite createSprite(TileConstants::TileColor color) const;

        static auto moveRelativeTo(sf::Sprite& sourceSprite, const sf::Sprite& relateSprite,
                                   TileConstants::TileDirection direction) -> void;
    };
}
