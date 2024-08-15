#pragma once

namespace Tetris
{
    struct GameConfig {
        static constexpr float DROP_INTERVAL = 1.0f;
        static constexpr float INPUT_INTERVAL = 0.1f;
        static constexpr float MIN_DROP_SPEED = 0.1f;
        static constexpr float SPEED_INCREASE_PER_LEVEL = 0.1f;
        static constexpr int INITIAL_PIECE_X = 4;
        static constexpr int INITIAL_PIECE_Y = 0;
    };
}
