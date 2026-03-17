#pragma once

/* 引擎有关头文件 */
#include "Application.h"
#include "InputManager.h"
#include "ShaderProgram.h"
#include "Renderer.h"
#include "Material.h"
#include "Mesh.h"
#include "GameObject.h"
#include "Scene.h"

#include <memory>
#include <chrono>

struct GLFWwindow;

namespace eng
{    
    class Engine
    {
    public:
        static Engine& GetInstance();

    private:
        // 私有创建 只允许获取单例
        Engine() = default;
        // 禁用拷贝移动
        Engine(const Engine&) = delete;
        Engine(Engine&&) = delete;
        Engine& operator=(const Engine&) = delete;
        Engine& operator=(Engine&&) = delete;

    public:
        bool Init(int width, int height);
        void Run();
        void Destroy();

        void SetApplication(Application* app);
        Application* GetApplication();

        InputManager& GetInputManager();
        Renderer& GetRenderer();
    
    private:
        std::unique_ptr<Application> m_application;
        std::chrono::high_resolution_clock::time_point m_lastTimePoint;
        GLFWwindow* m_window = nullptr;
        InputManager m_inputManager;
        Renderer m_renderer;
    };
}