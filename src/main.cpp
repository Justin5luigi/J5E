#include "game.hpp"

int main()
{
    Game game;
    game.Initialize();
    game.Setup();
    game.Run();
    game.Destroy();
    return 0;
}
