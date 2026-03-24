#include "game.h"
#include "engine.h"

int main()
{
    Game* game = new Game();
    Engine engine;
    engine.SetApplication(game);

    if (engine.Init())
    {
        engine.Run();
    }

    engine.Destroy();
    delete game;
    return 0;
}