#include "raylib-cpp.hpp"
#include "GameSettings.h"
#include "GameLoop.h"

int main()
{
    // Initialize Raylib
    GameLoop game{GAMEWIDTH, GAMEHEIGHT, GAMETITLE};
    game.run();

    return 0;
}
