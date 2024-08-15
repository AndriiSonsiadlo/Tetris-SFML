#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

#include "TileManager.h"
#include "TetrominoConst.h"

namespace Tetris
{
    class TetrominoManager
    {
    private:
        TileManager& tileManager;

    public:
        explicit TetrominoManager(TileManager& tileManager);

        [[nodiscard]] std::vector<sf::Sprite> createTetrominoSprites(
            TetrominoType type) const;
    };
}
