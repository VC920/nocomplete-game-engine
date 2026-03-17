#include "Engine.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

namespace eng
{
    void keyCallback(GLFWwindow* window, int key, int, int action, int)
    {
        auto& inputManager = eng::Engine::GetInstance().GetInputManager();
        if (action == GLFW_PRESS)
        {
            // 键盘按下
            inputManager.SetKeyPressed(key, true);
        }
        else if (action == GLFW_RELEASE)
        {
            // 键盘抬起
            inputManager.SetKeyPressed(key, false);
        }
    }

    void framebufferSizeCallback(GLFWwindow* window, int width, int height)
    {
        auto& renderer = eng::Engine::GetInstance().GetRenderer();
        renderer.SetViewport(width, height);
    }

    Engine& Engine::GetInstance()
    {
        static Engine instance;
        return instance;
    }

    bool Engine::Init(int width, int height)
    {
        if (!m_application)
        {
            return false;
        }

        // 初始化 GLFW
        if(!glfwInit())
        {
            return false;
        }

        // 配置 GLFW
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        // 创建窗口
        m_window = glfwCreateWindow(width, height, "mini engine", nullptr, nullptr);
        if (m_window == nullptr)
        {
            std::cout << "Error creating window" << std::endl;
            glfwTerminate();
            return false;
        }

        // 设置按键回调函数
        glfwSetKeyCallback(m_window, keyCallback);
        // 设置窗口回调函数
        glfwSetFramebufferSizeCallback(m_window, framebufferSizeCallback);
        // 设置当前窗口上下文
        glfwMakeContextCurrent(m_window);
        // 设置垂直同步
        glfwSwapInterval(1);

        // 加载 OpenGL 函数
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            std::cout << "Error initialize GLAD" << std::endl;
            glfwTerminate();
            return false;
        }

        // APP 初始化
        return m_application->Init();
    }

    void Engine::Run()
    {
        if (!m_application)
        {
            return;
        }

        m_lastTimePoint = std::chrono::high_resolution_clock::now();
        while (!glfwWindowShouldClose(m_window) && !m_application->NeedsToBeClosed())
        {
            // 拉取事件
            glfwPollEvents();

            // 计算 deltaTime
            auto now = std::chrono::high_resolution_clock::now();
            float deltaTime = std::chrono::duration<float>(now - m_lastTimePoint).count();
            m_lastTimePoint = now;

            // APP 更新
            m_application->Update(deltaTime);

            // 清除缓冲区
            m_renderer.SetClearColor(1.0f, 1.0f, 1.0f, 1.0f);
            m_renderer.ClearBuffers();

            m_renderer.Flush();

            // 交换缓冲区
            glfwSwapBuffers(m_window);
        }
    }

    void Engine::Destroy()
    {
        if (m_application)
        {
            // APP 清理
            m_application->Destroy();
            m_application.reset();
            glfwTerminate();
            m_window = nullptr;
        }
    }

    void Engine::SetApplication(Application* app)
    {
        m_application.reset(app);
    }

    Application* Engine::GetApplication()
    {
        return m_application.get();
    }

    InputManager& Engine::GetInputManager()
    {
        return m_inputManager;
    }

    Renderer& Engine::GetRenderer()
    {
        return m_renderer;
    }
}