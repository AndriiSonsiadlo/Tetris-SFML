#pragma once

#include <SFML/Graphics.hpp>

// @formatter:off
namespace Tetris::TileConstants
{
    enum class TileDirection
    {
        UP    = 0,
        RIGHT = 1,
        DOWN  = 2,
        LEFT  = 3
    };

    enum class TileColor
    {
        CYAN        = 0,
        BLUE        = 1,
        PURPLE      = 2,
        PINK        = 3,
        LIGHT_GREEN = 4,
        YELLOW      = 5,
        RED         = 6,
        GREEN       = 7,
        COUNT       = 8
    };

    constexpr int TILE_SIZE   = 30;
    constexpr int TILES_COUNT = static_cast<int>(TileColor::COUNT);

    inline std::unordered_map<TileColor, sf::IntRect> TILE_RECT_MAP = {
        {TileColor::CYAN,        sf::IntRect({  0, 0}, {TILE_SIZE, TILE_SIZE})},
        {TileColor::BLUE,        sf::IntRect({ 30, 0}, {TILE_SIZE, TILE_SIZE})},
        {TileColor::PURPLE,      sf::IntRect({ 60, 0}, {TILE_SIZE, TILE_SIZE})},
        {TileColor::PINK,        sf::IntRect({ 90, 0}, {TILE_SIZE, TILE_SIZE})},
        {TileColor::LIGHT_GREEN, sf::IntRect({120, 0}, {TILE_SIZE, TILE_SIZE})},
        {TileColor::YELLOW,      sf::IntRect({150, 0}, {TILE_SIZE, TILE_SIZE})},
        {TileColor::RED,         sf::IntRect({180, 0}, {TILE_SIZE, TILE_SIZE})},
        {TileColor::GREEN,       sf::IntRect({210, 0}, {TILE_SIZE, TILE_SIZE})}
    };
}
// @formatter:on
