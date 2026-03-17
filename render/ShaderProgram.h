#pragma once
#include <glad/glad.h>
#include <string>
#include <unordered_map>

namespace eng
{
    class ShaderProgram
    {
    public:
        ShaderProgram(const std::string& vertexSource, const std::string& fragmentSource);
        ~ShaderProgram();
    private:
        GLuint CompileShader(GLenum type, const std::string& source);
        GLuint LinkShader(GLuint vertexShader, GLuint fragmentShader);
        GLint GetUniformLocation(const std::string& name);
    public:
        void Bind();
        void SetUniform(const std::string& name, float value);
        void SetUniform(const std::string& name, float v0, float v1);
    private:
        std::unordered_map<std::string, GLint> m_uniformLocationCache;
        GLuint m_ShaderProgramID = 0;
    };   
}