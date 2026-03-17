#include "Mesh.h"

namespace eng
{
    Mesh::Mesh(const VertexLayout& layout, const std::vector<float>& vertices, const std::vector<uint32_t>& indices)
    {
        // 顶点布局
        m_vertexLayout = layout;

        // 绑定VAO
        glGenVertexArrays(1, &m_VAO);
        glBindVertexArray(m_VAO);

        // 绑定VBO
        glGenBuffers(1, &m_VBO);
        glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

        // 设置顶点属性
        for (auto& element : m_vertexLayout.elements)
        {
            glVertexAttribPointer(element.index, element.size, element.type, GL_FALSE, 
                m_vertexLayout.stride, (void*)(uintptr_t)element.offset);
            glEnableVertexAttribArray(element.index);
        }

        // 绑定EBO
        glGenBuffers(1, &m_EBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(uint32_t), indices.data(), GL_STATIC_DRAW);
        
        // 解绑
        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

        // 计算顶点和索引数量
        m_vertexCount = (vertices.size() * sizeof(float)) / m_vertexLayout.stride;
        m_indexCount = indices.size();
    }

    Mesh::Mesh(const VertexLayout& layout, const std::vector<float>& vertices)
    {
        // 顶点布局
        m_vertexLayout = layout;

        // 绑定VAO
        glGenVertexArrays(1, &m_VAO);
        glBindVertexArray(m_VAO);

        // 绑定VBO
        glGenBuffers(1, &m_VBO);
        glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

        // 设置顶点属性
        for (auto& element : m_vertexLayout.elements)
        {
            glVertexAttribPointer(element.index, element.size, element.type, GL_FALSE, 
                m_vertexLayout.stride, (void*)(uintptr_t)element.offset);
            glEnableVertexAttribArray(element.index);
        }
        
        // 解绑
        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        // 计算顶点数量
        m_vertexCount = (vertices.size() * sizeof(float)) / m_vertexLayout.stride;
    }

    Mesh::~Mesh()
    {
        glDeleteVertexArrays(1, &m_VAO);
        glDeleteBuffers(1, &m_VBO);
        glDeleteBuffers(1, &m_EBO);
    }

    void Mesh::Bind()
    {
        glBindVertexArray(m_VAO);
    }

    void Mesh::Draw()
    {
        // 使用索引绘制
        if (m_indexCount > 0)
        {
            glDrawElements(GL_TRIANGLES, m_indexCount, GL_UNSIGNED_INT, 0);
        }
        // 不使用索引绘制
        else
        {
            glDrawArrays(GL_TRIANGLES, 0, m_vertexCount);
        }
    }
}