#include "include/GameUI.h"
#include <iostream>

#include "GameBackground.h"

namespace Tetris
{
    GameUI::GameUI(sf::RenderWindow& window) : levelText(font), scoreText(font), linesClearedText(font),
                                               background("../assets/img4.jpg", "../assets/img2.jpg"), window(window)
    {
        if (!font.openFromFile("../fonts/200-x-light.otf"))
        {
            std::cerr << "Failed to load font. Using default font." << std::endl;
            if (!font.openFromFile("C:/Windows/Fonts/300-light.otf"))
            {
                std::cerr << "Failed to load default font." << std::endl;
                throw std::runtime_error("Font loading failed");
            };
        }

        setupUI();
    }

    void GameUI::setupUI()
    {
        gameBoard.setSize(sf::Vector2f(250, 600));
        gameBoard.setPosition({50, 50});
        gameBoard.setFillColor(sf::Color(20, 20, 40, 150));
        gameBoard.setOutlineColor(sf::Color(100, 150, 200, 200));
        gameBoard.setOutlineThickness(2);

        sidePanel.setSize(sf::Vector2f(200, 600));
        sidePanel.setPosition({320, 50});
        sidePanel.setFillColor(sf::Color(10, 10, 30, 180));
        sidePanel.setOutlineColor(sf::Color(80, 120, 160, 200));
        sidePanel.setOutlineThickness(2);

        levelText.setFont(font);
        levelText.setString("LEVEL\n1");
        levelText.setCharacterSize(24);
        levelText.setFillColor(sf::Color::White);
        levelText.setPosition({340, 80});

        scoreText.setFont(font);
        scoreText.setString("SCORE\n0");
        scoreText.setCharacterSize(24);
        scoreText.setFillColor(sf::Color::White);
        scoreText.setPosition({340, 200});

        linesClearedText.setFont(font);
        linesClearedText.setString("LINES\nCLEARED\n0");
        linesClearedText.setCharacterSize(24);
        linesClearedText.setFillColor(sf::Color::White);
        linesClearedText.setPosition({340, 320});
    }

    void GameUI::updateLevel(const unsigned int level)
    {
        levelText.setString("LEVEL\n" + std::to_string(level));
    }

    void GameUI::updateScore(const unsigned int score)
    {
        scoreText.setString("SCORE\n" + std::to_string(score));
    }

    void GameUI::updateLines(const unsigned int lines)
    {
        linesClearedText.setString("LINES\nCLEARED\n" + std::to_string(lines));
    }

    void GameUI::draw() const
    {
        background.draw(window);
        window.draw(gameBoard);
        window.draw(sidePanel);
        window.draw(levelText);
        window.draw(scoreText);
        window.draw(linesClearedText);
    }

    void GameUI::displayGameStats(const GameStats &stats)
    {
        updateLevel(stats.getLevel());
        updateScore(stats.getScore());
        updateLines(stats.getLinesCleared());
    }

    void GameUI::displayGameScreen(GameState state) const
    {
        if (state == GameState::Start)
        {
            sf::Text startText(font, "Press Enter to Start", 30);
            startText.setFillColor(sf::Color::White);
            startText.setPosition({
                window.getSize().x / 2 - startText.getGlobalBounds().size.x / 2,
                window.getSize().y / 2 - startText.getGlobalBounds().size.y / 2
            });
            window.draw(startText);
        }
        else if (state == GameState::Play)
        {
            background.draw(window);
            window.draw(gameBoard);
            window.draw(sidePanel);
            window.draw(levelText);
            window.draw(scoreText);
            window.draw(linesClearedText);
        }
        else if (state == GameState::Pause){
            sf::Text pauseText(font, "Game Paused\nPress P to Resume", 30);
            pauseText.setFillColor(sf::Color::Yellow);
            pauseText.setPosition({
                window.getSize().x / 2 - pauseText.getGlobalBounds().size.x / 2,
                window.getSize().y / 2 - pauseText.getGlobalBounds().size.y / 2
            });
            window.draw(pauseText);
        }
        else if (state == GameState::GameOver)
        {
            sf::Text gameOverText(font, "Game Over! Press Enter to Restart", 30);
            gameOverText.setFillColor(sf::Color::Red);
            gameOverText.setPosition({
                window.getSize().x / 2 - gameOverText.getGlobalBounds().size.x / 2,
                window.getSize().y / 2 - gameOverText.getGlobalBounds().size.y / 2
            });
            window.draw(gameOverText);
        }
    }
}
