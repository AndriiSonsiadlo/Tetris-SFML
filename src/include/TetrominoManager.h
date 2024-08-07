#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

#include "TileManager.h"
#include "../const/TetrominoConstants.h"

namespace Tetris
{
    class TetrominoManager
    {
    private:
        TileManager& tileManager;

    public:
        explicit TetrominoManager(TileManager& tileManager);

        [[nodiscard]] std::vector<sf::Sprite> createTetrominoSprites(
            TetrominoConstants::TetrominoType type) const;

        static TileConstants::TileColor getTetrominoColor(TetrominoConstants::TetrominoType type);
    };
}
