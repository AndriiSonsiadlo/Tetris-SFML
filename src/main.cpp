#include <iostream>

#include "Game.h"


int main()
{
    try
    {
        Tetris::Game game(600, 800, "Tetris");
        game.run();
    }
    catch (const std::exception& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}
