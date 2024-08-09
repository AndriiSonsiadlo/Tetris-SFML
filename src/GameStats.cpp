#include "include/GameStats.h"

#include <SFML/Graphics.hpp>


GameStats::GameStats() = default;

std::string GameStats::nums_directory = "/number_pngs";

int GameStats::getScore() const
{
    return score;
}

int GameStats::getLevel() const {
    return level;
}

int GameStats::getTime() const
{
    return timeInSeconds;
}

int GameStats::getLinesCleared() const {
    return linesCleared;
}

void GameStats::addLinesCleared(int n) {
    addScore(n);
    int old_lines = linesCleared;
    linesCleared += n;

    if (linesCleared % 10 < 4 && old_lines % 10 >= 4) {
        level++;
    }
}

void GameStats::addTimeInSeconds(const int seconds) {
    timeInSeconds += seconds;
}

void GameStats::addScore(const int lines) {
    int x = 0;
    switch(lines) {
        case 1:
            x = 40;
            break;
        case 2:
            x = 80;
            break;
        case 3:
            x = 300;
            break;
        case 4:
            x = 1200;
            break;
        default:
            x = 0;
    }

    score += x * (level+1);
}

void GameStats::printStatsToWindow(sf::RenderWindow& window) {

}
