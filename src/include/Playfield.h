#pragma once

#include <array>
#include <vector>
#include <SFML/System/Vector2.hpp>

class Playfield {
public:
    static constexpr int WIDTH  = 10;
    static constexpr int HEIGHT = 24;

    enum class Cell : int {
        Empty  = 0,
        Filled = 1
    };

private:
    std::array<std::array<Cell, WIDTH>, HEIGHT> grid{};

public:
    Playfield();

    [[nodiscard]] bool isInBounds(int x, int y) const;
    [[nodiscard]] bool isCellEmpty(int x, int y) const;

    void setCell(int x, int y, Cell value);
    [[nodiscard]] Cell getCell(int x, int y) const;

    [[nodiscard]] bool canPlacePiece(const std::vector<sf::Vector2i>& coords) const;
    void placePiece(const std::vector<sf::Vector2i>& coords, Cell value = Cell::Filled);
    void clearPiece(const std::vector<sf::Vector2i>& coords);

    [[nodiscard]] bool isLineFull(int y) const;
    void clearLine(int y);
    void shiftDownFrom(int row);
    int checkAndClearLines();
    void clearAllLines();

    [[nodiscard]] bool isGameOver() const;
};
