#include "Game.h"
#include "Engine.h"

int main()
{
    // 初始化引擎和游戏
    Game* game = new Game();
    eng::Engine& engine = eng::Engine::GetInstance();
    engine.SetApplication(game);

    // 运行引擎
    if (engine.Init(1280, 720))
    {
        engine.Run();
    }

    // 退出引擎
    engine.Destroy();
    return 0;
}