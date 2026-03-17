#pragma once
#include <glad/glad.h>
#include <vector>

namespace eng
{
    // 顶点元素信息
    struct VertexElement
    {
        GLuint index; // 顶点索引
        GLuint size; // 数据数量
        GLuint type; // 数据类型
        uint32_t offset; // 距离顶点开始的偏移字节数
    };
    
    // 顶点布局
    struct VertexLayout
    {
        std::vector<VertexElement> elements; // 顶点元素集合 
        uint32_t stride = 0; // 单个顶点的大小
    };

    class Mesh
    {
    public:
        Mesh(const VertexLayout& layout, const std::vector<float>& vertices, const std::vector<uint32_t>& indices);
        Mesh(const VertexLayout& layout, const std::vector<float>& vertices);
        ~Mesh();
        void Bind();
        void Draw();
    private:
        GLuint m_VAO = 0;
        GLuint m_VBO = 0;
        GLuint m_EBO = 0;
        VertexLayout m_vertexLayout;

        size_t m_vertexCount = 0;
        size_t m_indexCount = 0;
    };
}