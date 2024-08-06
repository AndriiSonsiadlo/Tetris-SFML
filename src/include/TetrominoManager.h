#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

#include "TileManager.h"
#include "../const/TetrominoConstants.h"

class TetrominoManager {
private:
    TileManager& tileManager;

public:
    explicit TetrominoManager(TileManager& tileManager);

    [[nodiscard]] std::vector<sf::Sprite> createTetrominoSprites(Tetris::TetrominoConstants::TetrominoType type) const;

    static Tetris::TileConstants::TileColor getTetrominoColor(Tetris::TetrominoConstants::TetrominoType type);
};