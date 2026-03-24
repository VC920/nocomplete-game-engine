#pragma once
#include <chrono>

class Application;
class Engine
{
public:
    bool Init();
    void Run();
    void Destroy();

    void SetApplication(Application* app);
    Application* GetApplication();

private:
    Application* m_application;
    std::chrono::high_resolution_clock::time_point m_lastTime;
};
