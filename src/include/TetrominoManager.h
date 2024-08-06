#pragma once

#include <SFML/Graphics.hpp>

#include "TileManager.h"

class TetrominoManager {
private:
    TileManager& tileManager;

public:
    explicit TetrominoManager(TileManager& tileManager);

};