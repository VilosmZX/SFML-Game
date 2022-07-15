#include <iostream>
#include "Game.h"


int main()
{
    std::srand(static_cast<unsigned>(std::time(NULL)));

    Game game;
    while (game.isRunning())
    {
        game.pollEvents();
        game.update();
        game.render();
    }
    return 0;
}