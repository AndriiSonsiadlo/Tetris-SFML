#pragma once

#include <SFML/Graphics.hpp>

class GameStats {
private:
    int score = 0;
    int level = 1;
    int linesCleared = 0;
    int timeInSeconds = 0;

    static std::string nums_directory;

    void addScore(int);
public:
    GameStats();

    [[nodiscard]] int getScore() const;
    [[nodiscard]] int getLevel() const;
    [[nodiscard]] int getLinesCleared() const;
    [[nodiscard]] int getTime() const;
    void addLinesCleared(int);
    void addTimeInSeconds(int);
    void printStatsToWindow(sf::RenderWindow&);
};
