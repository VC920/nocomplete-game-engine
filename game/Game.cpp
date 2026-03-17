#include "Game.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>

bool Game::Init()
{
    // 顶点着色器
    std::string vertexShaderSource = R"(
        #version 330 core
        layout (location = 0) in vec3 position;
        layout (location = 1) in vec3 color;

        out vec3 vColor;

        uniform vec2 uOffset;

        void main()
        {
            vColor = color;
            gl_Position = vec4(position.x + uOffset.x, position.y + uOffset.y, position.z, 1.0);
        }
    )";

    // 片段着色器
    std::string fragmentShaderSource = R"(
        #version 330 core
        out vec4 FragColor;

        in vec3 vColor;

        void main()
        {
            FragColor = vec4(vColor, 1.0);
        }
    )";

    // 创建着色器程序
    auto shaderProgram = std::make_shared<eng::ShaderProgram>(vertexShaderSource, fragmentShaderSource);

    // 设置材质
    m_material = std::make_unique<eng::Material>(shaderProgram);

    // 顶点信息
    std::vector<float> vertices = 
    {
        0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
        -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f,
        0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 0.0f
    };

    // 索引信息
    std::vector<unsigned int> indices = 
    {
        0, 1, 2,
        0, 2, 3
    };

    // 设置顶点布局
    eng::VertexLayout vertexLayout;
    vertexLayout.elements.push_back({0, 3, GL_FLOAT, 0});                   // 顶点位置
    vertexLayout.elements.push_back({1, 3, GL_FLOAT, 3 * sizeof(float)});   // 颜色
    vertexLayout.stride = 6 * sizeof(float);                                // 步长

    // 设置网格
    m_mesh = std::make_unique<eng::Mesh>(vertexLayout, vertices, indices);

    return true;
}

void Game::Update(float deltaTime)
{
    auto& renderer = eng::Engine::GetInstance().GetRenderer();
    auto& input = eng::Engine::GetInstance().GetInputManager();

    // 垂直移动
    if (input.IsKeyPressed(GLFW_KEY_W))
    {
        m_offsetY += 0.01f;
    }
    if (input.IsKeyPressed(GLFW_KEY_S))
    {
        m_offsetY -= 0.01f;
    }

    // 水平移动
    if (input.IsKeyPressed(GLFW_KEY_D))
    {
        m_offsetX += 0.01f;
    }
    if (input.IsKeyPressed(GLFW_KEY_A))
    {
        m_offsetX -= 0.01f;
    }

    m_material->SetFloat("uOffset", m_offsetX, m_offsetY);

    // 提交渲染命令
    eng::RenderCommand command;
    command.material = m_material.get();
    command.mesh = m_mesh.get();
    renderer.Submit(command);
}

void Game::Destroy()
{

}