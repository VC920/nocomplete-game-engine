#include "engine.h"
#include "application.h"

bool Engine::Init()
{
    if (!m_application)
    {
        return false;
    }
    return m_application->Init();
}

void Engine::Run()
{
    if (!m_application)
    {
        return;
    }

    m_lastTime = std::chrono::high_resolution_clock::now();
    while (!m_application->ShouldClosed())
    {
        auto currentTime = std::chrono::high_resolution_clock::now();
        float deltaTime = std::chrono::duration<float>(currentTime - m_lastTime).count();
        m_lastTime = currentTime;

        m_application->Update(deltaTime);
    }
}

void Engine::Destroy()
{
    if (m_application)
    {
        m_application->Destroy();
        m_application = nullptr;
    }
}

void Engine::SetApplication(Application* app)
{
    m_application = app;
}

Application* Engine::GetApplication()
{
    return m_application;
}
