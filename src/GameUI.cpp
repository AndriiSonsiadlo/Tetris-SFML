#include "include/GameUI.h"
#include <iostream>

GameUI::GameUI() : levelText(font), scoreText(font), linesClearedText(font)
{
    if (!font.openFromFile("../fonts/ARIAL.TTF"))
    {
        std::cerr << "Failed to load font. Using default font." << std::endl;
        if (!font.openFromFile("C:/Windows/Fonts/arial.ttf"))
        {
            std::cerr << "Failed to load default font." << std::endl;
            throw std::runtime_error("Font loading failed");
        };
    }

    setupUI();
}

void GameUI::setupUI()
{
    gameBoard.setSize(sf::Vector2f(400, 600));
    gameBoard.setPosition({50, 50});
    gameBoard.setFillColor(sf::Color(20, 20, 40, 150));
    gameBoard.setOutlineColor(sf::Color(100, 150, 200, 200));
    gameBoard.setOutlineThickness(2);

    sidePanel.setSize(sf::Vector2f(200, 600));
    sidePanel.setPosition({470, 50});
    sidePanel.setFillColor(sf::Color(10, 10, 30, 180));
    sidePanel.setOutlineColor(sf::Color(80, 120, 160, 200));
    sidePanel.setOutlineThickness(2);

    levelText.setFont(font);
    levelText.setString("LEVEL\n1");
    levelText.setCharacterSize(24);
    levelText.setFillColor(sf::Color::White);
    levelText.setPosition({490, 80});

    scoreText.setFont(font);
    scoreText.setString("SCORE\n0");
    scoreText.setCharacterSize(24);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition({490, 200});

    linesClearedText.setFont(font);
    linesClearedText.setString("LINES\nCLEARED\n0");
    linesClearedText.setCharacterSize(20);
    linesClearedText.setFillColor(sf::Color::White);
    linesClearedText.setPosition({490, 320});
}

void GameUI::updateLevel(const int level)
{
    levelText.setString("LEVEL\n" + std::to_string(level));
}

void GameUI::updateScore(const int score)
{
    scoreText.setString("SCORE\n" + std::to_string(score));
}

void GameUI::updateLines(const int lines)
{
    linesClearedText.setString("LINES\nCLEARED\n" + std::to_string(lines));
}
