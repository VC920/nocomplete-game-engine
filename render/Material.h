#pragma once
#include "ShaderProgram.h"
#include <memory>
#include <unordered_map>
#include <string>

namespace eng
{
    class Material
    {
    public:
        Material(const std::shared_ptr<ShaderProgram>& shaderProgram);
        void SetShaderProgram(const std::shared_ptr<ShaderProgram>& shaderProgram);
        void SetFloat(const std::string& name, float value);
        void SetFloat(const std::string& name, float v0, float v1);
        void Bind();

    private:
        std::shared_ptr<ShaderProgram> m_shaderProgram;
        std::unordered_map<std::string, float> m_floats;
        std::unordered_map<std::string, std::pair<float, float>> m_float2s;
    };   
}