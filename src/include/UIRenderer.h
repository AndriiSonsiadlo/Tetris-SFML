#pragma once

#include <SFML/Graphics.hpp>
#include <memory>

#include "TileManager.h"

namespace Tetris
{
    class GameController;

    struct UILayout
    {
        sf::Vector2f windowSize;

        sf::Vector2f boardPosition;
        sf::Vector2f boardSize;

        sf::Vector2f sidePanelPosition;
        sf::Vector2f sidePanelSize;

        sf::Vector2f nextPanelPosition;
        sf::Vector2f nextPanelSize;

        sf::Vector2f levelTextPos;
        sf::Vector2f scoreTextPos;
        sf::Vector2f linesTextPos;
        sf::Vector2f nextTextPos;

        float tileSize;
        sf::Vector2f playFieldOffset;
        sf::Vector2f nextPieceOffset;

        UILayout();
    };

    class UIRenderer
    {
    public:
        explicit UIRenderer(sf::RenderWindow& window);
        ~UIRenderer() = default;

        bool initialize();
        void render(const GameController& controller);
        void clear() const;
        void display() const;

    private:
        sf::RenderWindow& window_;
        UILayout layout_;
        TileManager tileManager_;

        sf::Font font_;
        sf::Texture backgroundTexture_;
        sf::Texture foregroundTexture_;

        sf::Text levelText_;
        sf::Text scoreText_;
        sf::Text linesText_;
        sf::Text nextText_;

        sf::RectangleShape gameBoard_;
        sf::RectangleShape sidePanel_;
        sf::RectangleShape nextPiecePanel_;
        sf::RectangleShape playfieldBackground_;

        std::unique_ptr<sf::Sprite> backgroundSprite_;
        std::unique_ptr<sf::Sprite> foregroundSprite_;

        bool loadAssets();
        void setupUI();
        void setupText();
        void setupShapes();
        void setupSprites();

        void renderBackground() const;
        void renderForeground() const;
        void renderPlayfield(const GameController& controller) const;
        void renderCurrentPiece(const GameController& controller) const;
        void renderNextPiece(const GameController& controller) const;
        void renderUI(const GameController& controller);
        void renderGameState(const GameController& controller);
        void renderMessageScreen(const std::string& message, sf::Color color = sf::Color::White) const;

        void updateGameStats(const GameController& controller);
        static sf::Vector2f centerText(const sf::Text& text, sf::Vector2f containerSize, sf::Vector2f containerPos);
    };
}
