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
          , boardPosition(80.0f, 80.0f)
          , boardSize(300.0f, 600.0f)
          , sidePanelPosition(420.0f, 80.0f)
          , sidePanelSize(160.0f, 600.0f)
          , nextPanelPosition(440.0f, 140.0f)
          , nextPanelSize(120.0f, 120.0f)
          , nextTextPos(470.0f, 100.0f)
          , levelTextPos(440.0f, 300.0f)
          , scoreTextPos(440.0f, 370.0f)
          , linesTextPos(440.0f, 440.0f)
          , nextTextPos(480.0f, 100.0f)
          , tileSize(30.0f)
          , playFieldOffset(80.0f, 80.0f)
          , nextPieceOffset(470.0f, 110.0f)
    {
    }

    UIRenderer::UIRenderer(sf::RenderWindow& window)
        : window_(window)
          , levelText_(font_)
          , scoreText_(font_)
          , linesText_(font_)
          , nextText_(font_)
          , levelNumberText_(fontText_)
          , scoreNumberText_(fontText_)
          , linesNumberText_(fontText_)
          , timeNumberText_(fontText_)
          , levelText_(fontText_)
          , scoreText_(fontText_)
          , linesText_(fontText_)
          , nextText_(fontText_)
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
        if (!fontText_.openFromFile(FONTS_DIR "300-light.otf"))
        {
            std::cerr << "Failed to load font" << std::endl;
            return false;
        }

        if (!fontNumber_.openFromFile(FONTS_DIR "200-light.otf"))
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

        if (!foregroundTexture_.loadFromFile(ASSETS_DIR "img9.jpg"))
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
        levelNumberText_.setFont(fontNumber_);
        levelNumberText_.setString("1");
        levelNumberText_.setCharacterSize(24);
        levelNumberText_.setFillColor(sf::Color::White);
        levelNumberText_.setPosition(layout_.levelTextPos);

        levelText_.setFont(fontText_);
        levelText_.setString("LEVEL");
        levelText_.setCharacterSize(16);
        levelText_.setFillColor(sf::Color::White);
        levelText_.setPosition({layout_.levelTextPos.x, layout_.levelTextPos.y + 30.0f});

        scoreNumberText_.setFont(fontNumber_);
        scoreNumberText_.setString("0");
        scoreNumberText_.setCharacterSize(24);
        scoreNumberText_.setFillColor(sf::Color::White);
        scoreNumberText_.setPosition(layout_.scoreTextPos);

        scoreText_.setFont(fontText_);
        scoreText_.setString("SCORE");
        scoreText_.setCharacterSize(16);
        scoreText_.setFillColor(sf::Color::White);
        scoreText_.setPosition({layout_.scoreTextPos.x, layout_.scoreTextPos.y + 30.0f});

        linesNumberText_.setFont(fontNumber_);
        linesNumberText_.setString("0");
        linesNumberText_.setCharacterSize(24);
        linesNumberText_.setFillColor(sf::Color::White);
        linesNumberText_.setPosition(layout_.linesTextPos);

        linesText_.setFont(fontText_);
        linesText_.setString("LINES");
        linesText_.setCharacterSize(16);
        linesText_.setFillColor(sf::Color::White);
        linesText_.setPosition({layout_.linesTextPos.x, layout_.linesTextPos.y + 30.0f});

        nextText_.setFont(fontText_);
        nextText_.setString("NEXT");
        nextText_.setCharacterSize(20);
        nextText_.setFillColor(sf::Color::White);
        nextText_.setPosition(layout_.nextTextPos);
    }

    void UIRenderer::setupShapes()
    {
        gameBoard_.setSize({layout_.boardSize.x, layout_.boardSize.y});
        gameBoard_.setPosition({layout_.boardPosition.x, layout_.boardPosition.y});
        gameBoard_.setFillColor(sf::Color(25, 25, 50, 200));
        gameBoard_.setOutlineColor(sf::Color(100, 150, 220, 220));
        gameBoard_.setOutlineThickness(2.0f);

        sidePanel_.setSize(layout_.sidePanelSize);
        sidePanel_.setPosition(layout_.sidePanelPosition);
        sidePanel_.setFillColor(sf::Color(20, 20, 40, 180));
        sidePanel_.setOutlineColor(sf::Color(100, 150, 220, 220));
        sidePanel_.setOutlineThickness(2.0f);

        nextPiecePanel_.setSize(layout_.nextPanelSize);
        nextPiecePanel_.setPosition(layout_.nextPanelPosition);
        nextPiecePanel_.setFillColor(sf::Color(35, 35, 60, 200));
        nextPiecePanel_.setOutlineColor(sf::Color(120, 180, 250, 220));
        nextPiecePanel_.setOutlineThickness(1.0f);

        playfieldBackground_.setSize(sf::Vector2f(layout_.boardSize.x, layout_.boardSize.y));
        playfieldBackground_.setPosition({layout_.boardPosition.x, layout_.boardPosition.y});
        playfieldBackground_.setFillColor(sf::Color(255, 255, 255, 0));
    }

    void UIRenderer::setupSprites()
    {
        backgroundSprite_         = std::make_unique<sf::Sprite>(backgroundTexture_);
        const sf::Vector2u bgSize = backgroundTexture_.getSize();
        backgroundSprite_->setScale(
            {
                layout_.windowSize.x / bgSize.x,
                layout_.windowSize.y / bgSize.y
            }
        );

        foregroundSprite_         = std::make_unique<sf::Sprite>(foregroundTexture_);
        const sf::Vector2u fgSize = foregroundTexture_.getSize();
        float scaleX              = playfieldBackground_.getSize().x / fgSize.x;
        float scaleY              = playfieldBackground_.getSize().y / fgSize.y;
        foregroundSprite_->setScale({scaleX, scaleY});
        foregroundSprite_->setPosition(playfieldBackground_.getPosition());
    }

    void UIRenderer::render(const GameController& controller)
    {
        renderBackground();
        renderGameState(controller);
    }

    void UIRenderer::renderForeground() const
    {
        window_.draw(*foregroundSprite_);
    }

    void UIRenderer::renderBackground() const
    {
        window_.draw(*backgroundSprite_);
    }

    void UIRenderer::renderPlayfield(const GameController& controller) const
    {
        const auto& playfield = controller.getPlayfield();

        window_.draw(playfieldBackground_);

        for (int x = 0; x <= Playfield::WIDTH; ++x)
        {
            sf::RectangleShape line(sf::Vector2f(1.0f, layout_.boardSize.y));
            line.setPosition({layout_.playFieldOffset.x + x * layout_.tileSize, layout_.playFieldOffset.y});
            line.setFillColor(sf::Color(100, 100, 100, 100));
            window_.draw(line);
        }

        for (int y = 0; y <= Playfield::HEIGHT; ++y)
        {
            sf::RectangleShape line(sf::Vector2f(layout_.boardSize.x, 1.0f));
            line.setPosition({layout_.playFieldOffset.x, layout_.playFieldOffset.y + y * layout_.tileSize});
            line.setFillColor(sf::Color(100, 100, 100, 100));
            window_.draw(line);
        }

        for (int y = 0; y < Playfield::HEIGHT; ++y)
        {
            for (int x = 0; x < Playfield::WIDTH; ++x)
            {
                if (playfield.getCell(x, y) == Playfield::Cell::Filled)
                {
                    auto sprite = tileManager_.createSprite(playfield.getCellColor(x, y));
                    sprite.setPosition({
                        layout_.playFieldOffset.x + x * layout_.tileSize,
                        layout_.playFieldOffset.y + y * layout_.tileSize
                    });
                    window_.draw(sprite);
                }
            }
        }
    }

    void UIRenderer::renderCurrentPiece(const GameController& controller) const
    {
        const auto* piece = controller.getCurrentPiece();
        if (!piece) return;

        for (const auto& pos : piece->getPositions())
        {
            if (pos.x >= 0 && pos.x < Playfield::WIDTH && pos.y >= 0 && pos.y < Playfield::HEIGHT)
            {
                auto sprite = tileManager_.createSprite(piece->getColor());
                sprite.setPosition({
                    layout_.playFieldOffset.x + pos.x * layout_.tileSize,
                    layout_.playFieldOffset.y + pos.y * layout_.tileSize
                });
                window_.draw(sprite);
            }
        }
    }

    void UIRenderer::renderNextPiece(const GameController& controller) const
    {
        const auto* piece = controller.getNextPiece();
        if (!piece) return;

        constexpr float nextTileSize = 20.0f;

        sf::Vector2f pieceCenter = piece->getCenterPosition();

        sf::Vector2f panelCenter(
            layout_.nextPanelPosition.x + layout_.nextPanelSize.x / 2.0f,
            layout_.nextPanelPosition.y + layout_.nextPanelSize.y / 2.0f
        );

        float offsetX = panelCenter.x - (pieceCenter.x * nextTileSize);
        float offsetY = panelCenter.y - (pieceCenter.y * nextTileSize);

        for (const auto& pos : piece->getPositions())
        {
            auto sprite = tileManager_.createSprite(piece->getColor());
            sprite.setScale({0.625f, 0.625f});
            sprite.setPosition({
                layout_.nextPieceOffset.x + (pos.x + centerOffset.x) * nextTileSize,
                layout_.nextPieceOffset.y + (pos.y + centerOffset.y) * nextTileSize
            });
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
        window_.draw(levelNumberText_);
        window_.draw(scoreText_);
        window_.draw(scoreNumberText_);
        window_.draw(linesText_);
        window_.draw(linesNumberText_);
        window_.draw(nextText_);

        renderForeground();
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
                renderMessageScreen("Game Paused\n\nPress P to Resume", sf::Color::Yellow);
                break;
            case GameState::GameOver:
                renderUI(controller);
                renderMessageScreen("Game Over!\n\nPress Enter to Restart", sf::Color::Red);
                break;
        }
    }

    void UIRenderer::renderMessageScreen(const std::string& message, const sf::Color color) const
    {
        sf::Text text(fontText_, message, 30);
        text.setFillColor(color);

        const sf::FloatRect textBounds = text.getLocalBounds();
        text.setPosition(
            {
                (layout_.windowSize.x - textBounds.size.x) / 2.0f,
                (layout_.windowSize.y - textBounds.size.y) / 2.0f
            }
        );

        sf::RectangleShape overlay(layout_.windowSize);
        overlay.setFillColor(sf::Color(0, 0, 0, 150));
        window_.draw(overlay);

        window_.draw(text);
    }

    void UIRenderer::updateGameStats(const GameController& controller)
    {
        const auto& stats = controller.getStats();

        levelText_.setString("LEVEL\n" + std::to_string(stats.getLevel()));
        scoreText_.setString("SCORE\n" + std::to_string(stats.getScore()));
        linesText_.setString("LINES\n" + std::to_string(stats.getLinesCleared()));
        levelNumberText_.setString(std::to_string(stats.getLevel()));
        scoreNumberText_.setString(std::to_string(stats.getScore()));
        linesNumberText_.setString(std::to_string(stats.getLinesCleared()));
    }

    sf::Vector2f UIRenderer::centerText(const sf::Text& text, const sf::Vector2f containerSize,
                                        const sf::Vector2f containerPos)
    {
        const sf::FloatRect textBounds = text.getLocalBounds();
        return sf::Vector2f(
            {
                containerPos.x + (containerSize.x - textBounds.size.x) / 2.0f,
                containerPos.y + (containerSize.y - textBounds.size.y) / 2.0f
            }
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
