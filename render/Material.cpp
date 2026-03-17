#include "Material.h"

namespace eng
{
    Material::Material(const std::shared_ptr<ShaderProgram>& shaderProgram)
    {
        this->m_shaderProgram = shaderProgram;
    }

    void Material::SetShaderProgram(const std::shared_ptr<ShaderProgram>& shaderProgram)
    {
        this->m_shaderProgram = shaderProgram;
    }   

    void Material::SetFloat(const std::string& name, float value)
    {
        m_floats[name] = value;
    }

    void Material::SetFloat(const std::string& name, float v0, float v1)
    {
        m_float2s[name] = { v0, v1 };
    }

    void Material::Bind()
    {
        if (!m_shaderProgram)
        {
            return;
        }

        // 绑定
        m_shaderProgram->Bind();

        // 遍历并设置Uniform
        for (auto& v : m_floats)
        {
            m_shaderProgram->SetUniform(v.first, v.second);
        }

        for (auto& v : m_float2s)
        {
            m_shaderProgram->SetUniform(v.first, v.second.first, v.second.second);
        }
    }
}