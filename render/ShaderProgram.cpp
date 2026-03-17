#include "ShaderProgram.h"
#include <iostream>

namespace eng
{
    ShaderProgram::ShaderProgram(const std::string& vertexSource, const std::string& fragmentSource)
    {
        // 编译顶点着色器
        GLuint vertexShader = CompileShader(GL_VERTEX_SHADER, vertexSource);
        
        // 编译片段着色器
        GLuint fragmentShader = CompileShader(GL_FRAGMENT_SHADER,fragmentSource);

        // 链接着色器程序
        m_ShaderProgramID = LinkShader(vertexShader,fragmentShader);

        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
    }

    ShaderProgram::~ShaderProgram()
    {
        glDeleteProgram(m_ShaderProgramID);
    }

    GLuint ShaderProgram::CompileShader(GLenum type, const std::string& source)
    {
        // 编译着色器 
        GLuint shader = glCreateShader(type);
        const char* shaderCStr = source.c_str();
        glShaderSource(shader, 1, &shaderCStr, nullptr);
        glCompileShader(shader);

        // 错误提示
        GLint success;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (success == GL_FALSE)
        {
            char infoLog[512];
            glGetShaderInfoLog(shader, 512,  nullptr, infoLog);
            if (type == GL_VERTEX_SHADER)
                std::cerr << "ERROR:VERTEX_SHADER_COMPILATION_FAILED: " << infoLog << std::endl;
            else if (type == GL_FRAGMENT_SHADER)
                std::cerr << "ERROR:FRAGMENT_SHADER_COMPILATION_FAILED: " << infoLog << std::endl;
            return 0;
        }

        return shader;
    }

    GLuint ShaderProgram::LinkShader(GLuint vertexShader, GLuint fragmentShader)
    {
        // 链接程序
        GLuint program = glCreateProgram();
        glAttachShader(program, vertexShader);
        glAttachShader(program, fragmentShader);
        glLinkProgram(program);

        // 错误提示
        GLint success;
        glGetProgramiv(program, GL_LINK_STATUS, &success);
        if (success == GL_FALSE)
        {
            char infoLog[512];
            glGetProgramInfoLog(program, 512, nullptr, infoLog);
            std::cerr << "ERROR:SHADRE_PROGRAM_LINKING_FAILED: " << infoLog << std::endl;
            return 0;
        }

        return program;
    }

    GLint ShaderProgram::GetUniformLocation(const std::string& name)
    {
        auto it = m_uniformLocationCache.find(name);
        // 如果找到直接使用
        if (it != m_uniformLocationCache.end())
        {
            return it->second;
        }
        // 否则查找位置并存入缓存
        GLint location = glGetUniformLocation(m_ShaderProgramID, name.c_str());
        m_uniformLocationCache[name] = location;
        return location;
    }

    void ShaderProgram::Bind()
    {
        glUseProgram(m_ShaderProgramID);
    }

    void ShaderProgram::SetUniform(const std::string& name, float value)
    {
        GLuint location = GetUniformLocation(name);
        glUniform1f(location, value);
    }

    void ShaderProgram::SetUniform(const std::string& name, float v0, float v1)
    {
        GLuint location = GetUniformLocation(name);
        glUniform2f(location, v0, v1);
    }
}