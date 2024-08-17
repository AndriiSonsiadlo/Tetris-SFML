#include "UIRenderer.h"
#include "GameController.h"
#include "GameConfig.h"
#include "Tetromino.h"
#include "Playfield.h"
#include <iostream>

#define ASSETS_DIR "../assets/"
#define FONTS_DIR "../fonts/"

namespace Tetris
{
    UILayout::UILayout()
        : windowSize(GameConfig::WINDOW_WIDTH, GameConfig::WINDOW_HEIGHT)
        , boardPosition(50.0f, 50.0f)
        , boardSize(300.0f, 600.0f)
        , sidePanelPosition(370.0f, 50.0f)
        , sidePanelSize(200.0f, 600.0f)
        , nextPanelPosition(390.0f, 450.0f)
        , nextPanelSize(120.0f, 120.0f)
        , levelTextPos(390.0f, 80.0f)
        , scoreTextPos(390.0f, 180.0f)
        , linesTextPos(390.0f, 280.0f)
        , nextTextPos(420.0f, 420.0f)
        , tileSize(30.0f)
        , playFieldOffset(60.0f, 60.0f)
        , nextPieceOffset(430.0f, 480.0f)
    {
    }

    UIRenderer::UIRenderer(sf::RenderWindow& window)
        : window_(window)
        , levelText_(font_)
        , scoreText_(font_)
        , linesText_(font_)
        , nextText_(font_)
    {
    }

    bool UIRenderer::initialize()
    {
        if (!loadAssets())
        {
            return false;
        }

        setupUI();
        return true;
    }

    bool UIRenderer::loadAssets()
    {
        if (!font_.openFromFile(FONTS_DIR "200-x-light.otf"))
        {
            std::cerr << "Failed to load font" << std::endl;
            return false;
        }

        if (!tileManager_.loadTileTexture(ASSETS_DIR "tiles.png"))
        {
            std::cerr << "Failed to load tile texture" << std::endl;
            return false;
        }

        if (!backgroundTexture_.loadFromFile(ASSETS_DIR "img4.jpg"))
        {
            std::cerr << "Failed to load background texture" << std::endl;
            return false;
        }

        if (!foregroundTexture_.loadFromFile(ASSETS_DIR "img2.jpg"))
        {
            std::cerr << "Failed to load foreground texture" << std::endl;
            return false;
        }

        return true;
    }

    void UIRenderer::setupUI()
    {
        setupText();
        setupShapes();
        setupSprites();
    }

    void UIRenderer::setupText()
    {
        levelText_.setFont(font_);
        levelText_.setString("LEVEL\n1");
        levelText_.setCharacterSize(24);
        levelText_.setFillColor(sf::Color::White);
        levelText_.setPosition(layout_.levelTextPos);

        scoreText_.setFont(font_);
        scoreText_.setString("SCORE\n0");
        scoreText_.setCharacterSize(24);
        scoreText_.setFillColor(sf::Color::White);
        scoreText_.setPosition(layout_.scoreTextPos);

        linesText_.setFont(font_);
        linesText_.setString("LINES\n0");
        linesText_.setCharacterSize(24);
        linesText_.setFillColor(sf::Color::White);
        linesText_.setPosition(layout_.linesTextPos);

        nextText_.setFont(font_);
        nextText_.setString("NEXT");
        nextText_.setCharacterSize(20);
        nextText_.setFillColor(sf::Color::White);
        nextText_.setPosition(layout_.nextTextPos);
    }

    void UIRenderer::setupShapes()
    {
        gameBoard_.setSize(layout_.boardSize);
        gameBoard_.setPosition(layout_.boardPosition);
        gameBoard_.setFillColor(sf::Color(20, 20, 40, 100));
        gameBoard_.setOutlineColor(sf::Color(100, 150, 200, 200));
        gameBoard_.setOutlineThickness(2.0f);

        sidePanel_.setSize(layout_.sidePanelSize);
        sidePanel_.setPosition(layout_.sidePanelPosition);
        sidePanel_.setFillColor(sf::Color(10, 10, 30, 150));
        sidePanel_.setOutlineColor(sf::Color(80, 120, 160, 200));
        sidePanel_.setOutlineThickness(2.0f);

        nextPiecePanel_.setSize(layout_.nextPanelSize);
        nextPiecePanel_.setPosition(layout_.nextPanelPosition);
        nextPiecePanel_.setFillColor(sf::Color(30, 30, 50, 180));
        nextPiecePanel_.setOutlineColor(sf::Color(100, 150, 200, 200));
        nextPiecePanel_.setOutlineThickness(1.0f);

        playfieldBackground_.setSize(sf::Vector2f(layout_.boardSize.x - 20.0f, layout_.boardSize.y - 20.0f));
        playfieldBackground_.setPosition({layout_.boardPosition.x + 10.0f, layout_.boardPosition.y + 10.0f});
        playfieldBackground_.setFillColor(sf::Color(255, 255, 255, 80));
    }

    void UIRenderer::setupSprites()
    {
        backgroundSprite_ = std::make_unique<sf::Sprite>(backgroundTexture_);
        const sf::Vector2u bgSize = backgroundTexture_.getSize();
        backgroundSprite_->setScale(
            {layout_.windowSize.x / bgSize.x,
            layout_.windowSize.y / bgSize.y}
        );

        foregroundSprite_ = std::make_unique<sf::Sprite>(foregroundTexture_);
        const sf::Vector2u fgSize = foregroundTexture_.getSize();
        float scaleX = playfieldBackground_.getSize().x / fgSize.x;
        float scaleY = playfieldBackground_.getSize().y / fgSize.y;
        foregroundSprite_->setScale({scaleX, scaleY});
        foregroundSprite_->setPosition(playfieldBackground_.getPosition());
    }

    void UIRenderer::render(const GameController& controller)
    {
        renderBackground();
        renderGameState(controller);
    }

    void UIRenderer::renderBackground()
    {
        window_.draw(*backgroundSprite_);
    }

    void UIRenderer::renderPlayfield(const GameController& controller)
    {
        const auto& playfield = controller.getPlayfield();

        window_.draw(playfieldBackground_);
        window_.draw(*foregroundSprite_);

        for (int y = 0; y < Playfield::HEIGHT; ++y)
        {
            for (int x = 0; x < Playfield::WIDTH; ++x)
            {
                if (playfield.getCell(x, y) == Playfield::Cell::Filled)
                {
                    auto sprite = tileManager_.createSprite(playfield.getCellColor(x, y));
                    sprite.setPosition(
                        {layout_.playFieldOffset.x + x * layout_.tileSize,
                        layout_.playFieldOffset.y + (y - 0) * layout_.tileSize}
                    );
                    window_.draw(sprite);
                }
            }
        }
    }

    void UIRenderer::renderCurrentPiece(const GameController& controller)
    {
        const auto* piece = controller.getCurrentPiece();
        if (!piece) return;

        for (const auto& pos : piece->getPositions())
        {
            if (pos.y >= 0)
            {
                auto sprite = tileManager_.createSprite(piece->getColor());
                sprite.setPosition(
                    {layout_.playFieldOffset.x + pos.x * layout_.tileSize,
                    layout_.playFieldOffset.y + pos.y * layout_.tileSize}
                );
                window_.draw(sprite);
            }
        }
    }

    void UIRenderer::renderNextPiece(const GameController& controller)
    {
        const auto* piece = controller.getNextPiece();
        if (!piece) return;

        const float nextTileSize = 20.0f;

        for (const auto& pos : piece->getPositions())
        {
            auto sprite = tileManager_.createSprite(piece->getColor());
            sprite.setScale({0.67f, 0.67f});
            sprite.setPosition(
                {layout_.nextPieceOffset.x + pos.x * nextTileSize,
                layout_.nextPieceOffset.y + pos.y * nextTileSize}
            );
            window_.draw(sprite);
        }
    }

    void UIRenderer::renderUI(const GameController& controller)
    {
        window_.draw(gameBoard_);
        window_.draw(sidePanel_);
        window_.draw(nextPiecePanel_);

        updateGameStats(controller);
        window_.draw(levelText_);
        window_.draw(scoreText_);
        window_.draw(linesText_);
        window_.draw(nextText_);

        renderPlayfield(controller);
        renderCurrentPiece(controller);
        renderNextPiece(controller);
    }

    void UIRenderer::renderGameState(const GameController& controller)
    {
        switch (controller.getGameState())
        {
            case GameState::Start:
                renderMessageScreen("Press Enter to Start");
                break;
            case GameState::Play:
                renderUI(controller);
                break;
            case GameState::Pause:
                renderUI(controller);
                renderMessageScreen("Game Paused\nPress P to Resume", sf::Color::Yellow);
                break;
            case GameState::GameOver:
                renderUI(controller);
                renderMessageScreen("Game Over!\nPress Enter to Restart", sf::Color::Red);
                break;
        }
    }

    void UIRenderer::renderMessageScreen(const std::string& message, const sf::Color color) const
    {
        sf::Text text(font_, message, 30);
        text.setFillColor(color);

        sf::FloatRect textBounds = text.getLocalBounds();
        text.setPosition(
            {(layout_.windowSize.x - textBounds.size.x) / 2.0f,
            (layout_.windowSize.y - textBounds.size.y) / 2.0f}
        );

        sf::RectangleShape overlay(layout_.windowSize);
        overlay.setFillColor(sf::Color(0, 0, 0, 128));
        window_.draw(overlay);

        window_.draw(text);
    }

    void UIRenderer::updateGameStats(const GameController& controller)
    {
        const auto& stats = controller.getStats();

        levelText_.setString("LEVEL\n" + std::to_string(stats.getLevel()));
        scoreText_.setString("SCORE\n" + std::to_string(stats.getScore()));
        linesText_.setString("LINES\n" + std::to_string(stats.getLinesCleared()));
    }

    sf::Vector2f UIRenderer::centerText(const sf::Text& text, const sf::Vector2f containerSize, const sf::Vector2f containerPos)
    {
        const sf::FloatRect textBounds = text.getLocalBounds();
        return sf::Vector2f(
{            containerPos.x + (containerSize.x - textBounds.size.x) / 2.0f,
            containerPos.y + (containerSize.y - textBounds.size.y) / 2.0f}
        );
    }

    void UIRenderer::clear() const
    {
        window_.clear();
    }

    void UIRenderer::display() const
    {
        window_.display();
    }
}