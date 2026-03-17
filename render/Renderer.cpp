#include "Renderer.h"
#include <glad/glad.h>
#include <iostream>

namespace eng
{
    void Renderer::BindMaterial(Material* material)
    {
        if (material)
        {
            material->Bind();
        }
    }

    void Renderer::BindMesh(Mesh* mesh)
    {
        if (mesh)
        {
            mesh->Bind();
        }
    }

    void Renderer::DrawMesh(Mesh* mesh)
    {
        if (mesh)
        {
            mesh->Draw();
        }
    }

    void Renderer::SetViewport(int width, int height)
    {
        glViewport(0, 0, width, height);
    }

    void Renderer::SetClearColor(float r, float g, float b, float a)
    {
        glClearColor(r, g, b, a);
    }

    void Renderer::ClearBuffers()
    {
        glClear(GL_COLOR_BUFFER_BIT);
    }

    void Renderer::Submit(const RenderCommand& command)
    {
        m_commmands.push_back(command);
    }

    void Renderer::Flush()
    {
        for (auto& commands : m_commmands)
        {
            BindMaterial(commands.material);
            BindMesh(commands.mesh);
            DrawMesh(commands.mesh);
        }

        m_commmands.clear();
    }
}