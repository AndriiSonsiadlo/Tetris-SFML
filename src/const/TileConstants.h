#pragma once

#include <SFML/Graphics.hpp>


namespace Tetris::TileConstants
{
    constexpr int TILE_SIZE = 30;
    constexpr int TILES_COUNT = 8;

    enum class TileDirection
    {
        UP = 0,
        RIGHT = 1,
        DOWN = 2,
        LEFT = 3
    };

    enum class TileColor
    {
        CYAN = 0,
        BLUE = 1,
        PURPLE = 2,
        PINK = 3,
        LIGHT_GREEN = 4,
        YELLOW = 5,
        RED = 6,
        GREEN = 7
    };

    constexpr sf::IntRect TILE_CYAN({0, 0}, {TILE_SIZE, TILE_SIZE});
    constexpr sf::IntRect TILE_BLUE({30, 0}, {TILE_SIZE, TILE_SIZE});
    constexpr sf::IntRect TILE_PURPLE({60, 0}, {TILE_SIZE, TILE_SIZE});
    constexpr sf::IntRect TILE_PINK({90, 0}, {TILE_SIZE, TILE_SIZE});
    constexpr sf::IntRect TILE_LIGHT_GREEN({120, 0}, {TILE_SIZE, TILE_SIZE});
    constexpr sf::IntRect TILE_YELLOW({150, 0}, {TILE_SIZE, TILE_SIZE});
    constexpr sf::IntRect TILE_RED({180, 0}, {TILE_SIZE, TILE_SIZE});
    constexpr sf::IntRect TILE_GREEN({210, 0}, {TILE_SIZE, TILE_SIZE});

    constexpr sf::IntRect TILE_RECTS[TILES_COUNT] = {
        TILE_CYAN, TILE_BLUE, TILE_PURPLE, TILE_PINK,
        TILE_LIGHT_GREEN, TILE_YELLOW, TILE_RED, TILE_GREEN
    };
}
