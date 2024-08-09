// GameBackground.cpp
#include "GameBackground.h"
#include <iostream>

namespace Tetris
{
    const char* const GameBackground::BACKGROUND_LOAD_ERROR = "Error loading background texture: ";
    const char* const GameBackground::FOREGROUND_LOAD_ERROR = "Error loading foreground texture: ";

    GameBackground::GameBackground(const std::string& backgroundPath, const std::string& foregroundPath)
    {
        if (!loadTextures(backgroundPath, foregroundPath))
        {
            throw std::runtime_error("Failed to load background or foreground textures");
        }
    }

    bool GameBackground::loadTexture(const std::string& path, sf::Texture& texture,
                                     std::shared_ptr<sf::Sprite>& sprite, const char* errorMsg)
    {
        if (!texture.loadFromFile(path))
        {
            std::cerr << errorMsg << path << std::endl;
            return false;
        }
        sprite = std::make_shared<sf::Sprite>(texture);
        return true;
    }

    bool GameBackground::loadTextures(const std::string& backgroundPath, const std::string& foregroundPath)
    {
        return loadTexture(backgroundPath, backgroundTexture, backgroundSprite, BACKGROUND_LOAD_ERROR) &&
            loadTexture(foregroundPath, foregroundTexture, foregroundSprite, FOREGROUND_LOAD_ERROR);
    }

    void GameBackground::setScale(float scaleX, float scaleY) const
    {
        backgroundSprite->setScale({scaleX, scaleY});
        foregroundSprite->setScale({scaleX, scaleY});
    }

    void GameBackground::setPosition(float x, float y) const
    {
        backgroundSprite->setPosition({x, y});
        foregroundSprite->setPosition({x, y});
    }

    void GameBackground::draw(sf::RenderWindow& window) const
    {
        window.draw(*backgroundSprite);
        window.draw(*foregroundSprite);
    }
}
