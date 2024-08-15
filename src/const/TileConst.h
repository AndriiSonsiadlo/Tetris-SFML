#pragma once

#include <SFML/Graphics.hpp>

#include "Enums.h"


namespace Tetris::TileConst
{
    constexpr int TILE_SIZE   = 30;
    constexpr int TILES_COUNT = static_cast<int>(TileColor::COUNT);

    inline std::unordered_map<TileColor, sf::IntRect> TILE_RECT_MAP = {
        {TileColor::CYAN, sf::IntRect({0, 0}, {TILE_SIZE, TILE_SIZE})},
        {TileColor::BLUE, sf::IntRect({30, 0}, {TILE_SIZE, TILE_SIZE})},
        {TileColor::PURPLE, sf::IntRect({60, 0}, {TILE_SIZE, TILE_SIZE})},
        {TileColor::PINK, sf::IntRect({90, 0}, {TILE_SIZE, TILE_SIZE})},
        {TileColor::LIGHT_GREEN, sf::IntRect({120, 0}, {TILE_SIZE, TILE_SIZE})},
        {TileColor::YELLOW, sf::IntRect({150, 0}, {TILE_SIZE, TILE_SIZE})},
        {TileColor::RED, sf::IntRect({180, 0}, {TILE_SIZE, TILE_SIZE})},
        {TileColor::GREEN, sf::IntRect({210, 0}, {TILE_SIZE, TILE_SIZE})}
    };
}
