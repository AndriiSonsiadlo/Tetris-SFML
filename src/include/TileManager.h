#pragma once

#include <SFML/Graphics.hpp>
#include <string>

#include "../const/TileConstants.h"

class TileManager
{
private:
    sf::Texture tileTexture;

public:
    TileManager();

    bool loadTileTexture(const std::string& filename);

    const sf::Texture& getTexture() const;

    static sf::IntRect getTileRect(Tetris::TileConstants::TileColor color);

    void setSpriteTile(sf::Sprite& sprite, Tetris::TileConstants::TileColor color) const;

    sf::Sprite createSprite(Tetris::TileConstants::TileColor color) const;
};
