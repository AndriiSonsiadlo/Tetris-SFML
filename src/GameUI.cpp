#include "GameUI.h"
#include "Tetromino.h"

#define ASSETS_DIR "../assets/"
#define FONTS_DIR "../fonts/"

namespace Tetris
{
    GameUI::GameUI(sf::RenderWindow& window, GameStats& stats, Playfield& playfield)
        : levelText(font),
          scoreText(font),
          linesClearedText(font),
          nextPieceText(font),
          window(window),
          stats(stats),
          playfield(playfield)
    {
        loadAssets();

        setupPlayScreen();
    }

    void GameUI::loadAssets()
    {
        if (!font.openFromFile(FONTS_DIR "200-x-light.otf"))
            throw std::runtime_error("Failed to load text font");
        if (!tileManager.loadTileTexture(ASSETS_DIR "tiles.png"))
            throw std::runtime_error("Failed to load tiles texture");
        if (!backgroundTexture.loadFromFile(ASSETS_DIR "img4.jpg") || !foregroundTexture.loadFromFile(ASSETS_DIR "img2.jpg"))
            throw std::runtime_error("Failed to load foreground or background texture");
    }

    void GameUI::setupPlayScreen()
    {
        gameBoard.setSize(sf::Vector2f(300, 600));
        gameBoard.setPosition({50, 50});
        gameBoard.setFillColor(sf::Color(20, 20, 40, 150));
        gameBoard.setOutlineColor(sf::Color(100, 150, 200, 200));
        gameBoard.setOutlineThickness(2);

        sidePanel.setSize(sf::Vector2f(200, 600));
        sidePanel.setPosition({370, 50});
        sidePanel.setFillColor(sf::Color(10, 10, 30, 180));
        sidePanel.setOutlineColor(sf::Color(80, 120, 160, 200));
        sidePanel.setOutlineThickness(2);

        nextPiecePanel.setSize(sf::Vector2f(120, 120));
        nextPiecePanel.setPosition({390, 450});
        nextPiecePanel.setFillColor(sf::Color(30, 30, 50, 200));
        nextPiecePanel.setOutlineColor(sf::Color(100, 150, 200, 200));
        nextPiecePanel.setOutlineThickness(1);

        levelText.setFont(font);
        levelText.setString("LEVEL\n1");
        levelText.setCharacterSize(24);
        levelText.setFillColor(sf::Color::White);
        levelText.setPosition({390, 80});

        scoreText.setFont(font);
        scoreText.setString("SCORE\n0");
        scoreText.setCharacterSize(24);
        scoreText.setFillColor(sf::Color::White);
        scoreText.setPosition({390, 180});

        linesClearedText.setFont(font);
        linesClearedText.setString("LINES\n0");
        linesClearedText.setCharacterSize(24);
        linesClearedText.setFillColor(sf::Color::White);
        linesClearedText.setPosition({390, 280});

        nextPieceText.setFont(font);
        nextPieceText.setString("NEXT");
        nextPieceText.setCharacterSize(20);
        nextPieceText.setFillColor(sf::Color::White);
        nextPieceText.setPosition({420, 420});
    }

    void GameUI::displayLevel(const unsigned int level)
    {
        levelText.setString("LEVEL\n" + std::to_string(level));
    }

    void GameUI::displayScore(const unsigned int score)
    {
        scoreText.setString("SCORE\n" + std::to_string(score));
    }

    void GameUI::displayLines(const unsigned int lines)
    {
        linesClearedText.setString("LINES\n" + std::to_string(lines));
    }

    void GameUI::displayPlayfield()
    {
        const float tileSize = 30.0f;
        const sf::Vector2f boardOffset(60, 60);

        for (int y = 4; y < Playfield::HEIGHT; ++y)
        {
            for (int x = 0; x < Playfield::WIDTH; ++x)
            {
                if (playfield.getCell(x, y) == Playfield::Cell::Filled)
                {
                    auto sprite = tileManager.createSprite(playfield.getCellColor(x, y));
                    sprite.setPosition({boardOffset.x + x * tileSize, boardOffset.y + (y - 4) * tileSize});
                    window.draw(sprite);
                }
            }
        }
    }

    void GameUI::displayCurrentPiece(const Tetromino* piece)
    {
        if (!piece) return;

        const float tileSize = 30.0f;
        const sf::Vector2f boardOffset(60, 60);

        for (const auto& pos : piece->getPositions())
        {
            if (pos.y >= 4)
            {
                auto sprite = tileManager.createSprite(piece->getColor());
                sprite.setPosition({boardOffset.x + pos.x * tileSize, boardOffset.y + (pos.y - 4) * tileSize});
                window.draw(sprite);
            }
        }
    }

    void GameUI::displayNextPiece(const Tetromino* piece)
    {
        if (!piece) return;

        const float tileSize = 20.0f;
        const sf::Vector2f nextOffset(430, 480);

        for (const auto& pos : piece->getPositions())
        {
            auto sprite = tileManager.createSprite(piece->getColor());
            sprite.setScale({0.67f, 0.67f});
            sprite.setPosition({nextOffset.x + pos.x * tileSize, nextOffset.y + pos.y * tileSize});
            window.draw(sprite);
        }
    }

    void GameUI::displayPlayScreen(const Tetromino* currentPiece, const Tetromino* nextPiece)
    {
        window.draw(sf::Sprite(backgroundTexture));

        window.draw(gv ameBoard);
        window.draw(sidePanel);
        window.draw(nextPiecePanel);
        window.draw(levelText);
        window.draw(scoreText);
        window.draw(linesClearedText);
        window.draw(nextPieceText);

        displayGameStats();
        displayPlayfield();
        displayCurrentPiece(currentPiece);
        displayNextPiece(nextPiece);
    }

    void GameUI::displayGameStats()
    {
        displayLevel(stats.getLevel());
        displayScore(stats.getScore());
        displayLines(stats.getLinesCleared());
    }

    void GameUI::displayMessageScreen(const std::string& textMessage, const sf::Color color) const
    {
        sf::Text text(font, textMessage, 30);
        text.setFillColor(color);
        text.setPosition({
            window.getSize().x / 2 - text.getGlobalBounds().size.x / 2,
            window.getSize().y / 2 - text.getGlobalBounds().size.y / 2
        });
        window.draw(text);
    }

    void GameUI::clearWindow() const
    {
        window.clear();
    }

    void GameUI::refreshWindow() const
    {
        window.display();
    }

    void GameUI::displayGameScreen(const GameState state, const Tetromino* currentPiece, const Tetromino* nextPiece)
    {
        if (state == GameState::Start)
            displayMessageScreen("Press Enter to Start");
        else if (state == GameState::Play)
        {
            displayPlayScreen(currentPiece, nextPiece);
        }
        else if (state == GameState::Pause)
            displayMessageScreen("Game Paused\nPress P to Resume", sf::Color::Yellow);
        else if (state == GameState::GameOver)
            displayMessageScreen("Game Over! Press Enter to Restart", sf::Color::Red);
    }
}
