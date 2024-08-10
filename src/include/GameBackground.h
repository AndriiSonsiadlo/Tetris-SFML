
// GameBackground.h
#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include <string>

namespace Tetris {
    class GameBackground {
    private:
        static const char* const BACKGROUND_LOAD_ERROR;
        static const char* const FOREGROUND_LOAD_ERROR;
        
        sf::Texture backgroundTexture;
        sf::Texture foregroundTexture;
        std::shared_ptr<sf::Sprite> backgroundSprite{nullptr};
        std::shared_ptr<sf::Sprite> foregroundSprite{nullptr};

        bool loadTexture(const std::string& path, sf::Texture& texture,
                        std::shared_ptr<sf::Sprite>& sprite, const char* errorMsg);
        
    public:
        GameBackground(const std::string& backgroundPath, const std::string& foregroundPath);
        
        bool loadTextures(const std::string& backgroundPath, const std::string& foregroundPath);
        void setScale(float scaleX, float scaleY) const;
        void setPosition(float x, float y) const;
        void draw(sf::RenderWindow& window) const;
        const sf::Texture* getBackgroundTexture() const;
        const sf::Texture* getForegroundTexture() const;
    };
}