#pragma once
#include "ShaderProgram.h"
#include "Material.h"
#include "Mesh.h"
#include <glad/glad.h>
#include <memory>
#include <string>
#include <vector>

namespace eng
{
    struct RenderCommand
    {
        Mesh* mesh = nullptr;
        Material* material = nullptr;
    };

    class Renderer
    {
    private:
        // 私有构造
        Renderer() = default;
        // 禁用拷贝移动 只允许Engine创建 
        Renderer(const Renderer&) = delete;
        Renderer(Renderer&&) = delete;
        Renderer& operator=(const Renderer&) = delete;
        Renderer& operator=(Renderer&&) = delete;

        void BindShaderProgram(ShaderProgram* shaderProgram);
        void BindMaterial(Material* material);
        void BindMesh(Mesh* mesh);
        void DrawMesh(Mesh* mesh);
        
    public:
        void SetViewport(int width, int height);
        void SetClearColor(float r, float g, float b, float a);
        void ClearBuffers();
        
        void Submit(const RenderCommand& command);
        void Flush();

    private:
        friend class Engine;
        std::vector<RenderCommand> m_commmands;
    };   
}