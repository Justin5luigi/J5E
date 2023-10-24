#include "game.hpp"

int main(int argc, char* argv[])
{
    Game game;
    game.Initialize();
    game.Setup();
    game.Run();
    game.Destroy();
    return 0;
}

//STILL TODO
//Create tilemap loader
//Create animation system
//Create sort by zidx
//Camera system
