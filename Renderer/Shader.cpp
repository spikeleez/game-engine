#include "Shader.h"
#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>
#include <stdexcept>

GameEngine::Renderer::Shader::Shader(const std::string& VertexSrc, const std::string& FragmentSrc)
{
    uint32_t VS = Compile(GL_VERTEX_SHADER, VertexSrc);
    uint32_t FS = Compile(GL_FRAGMENT_SHADER, FragmentSrc);

    RendererID = glCreateProgram();
    glAttachShader(RendererID, VS);
    glAttachShader(RendererID, FS);
    glLinkProgram(RendererID);

    int bLinked;
    glGetProgramiv(RendererID, GL_LINK_STATUS, &bLinked);
    if (!bLinked)
    {
        char Log[512];
        glGetProgramInfoLog(RendererID, 512, nullptr, Log);
        glDeleteProgram(RendererID);
        throw std::runtime_error(std::string("Shader link error.") + Log);
    }

    glDeleteShader(VS);
    glDeleteShader(FS);
}

GameEngine::Renderer::Shader::~Shader()
{
    glDeleteProgram(RendererID);
}

uint32_t GameEngine::Renderer::Shader::Compile(uint32_t Type, const std::string& Src)
{
    uint32_t ID = glCreateShader(Type);
    const char* Ptr = Src.c_str();
    glShaderSource(ID, 1, &Ptr, nullptr);
    glCompileShader(ID);

    int bCompiled;
    glGetShaderiv(ID, GL_COMPILE_STATUS, &bCompiled);
    if (!bCompiled)
    {
        char Log[512];
        glGetShaderInfoLog(ID, 512, nullptr, Log);
        glDeleteShader(ID);
        throw std::runtime_error(std::string("Shader compile error.") + Log);
    }

    return ID;
}

void GameEngine::Renderer::Shader::Bind() const
{
    glUseProgram(RendererID);
}

void GameEngine::Renderer::Shader::Unbind() const
{
    glUseProgram(0);
}

int GameEngine::Renderer::Shader::GetUniformLocation(const std::string& Name) const
{
    return glGetUniformLocation(RendererID, Name.c_str());
}

void GameEngine::Renderer::Shader::SetInt(const std::string& Name, int Value)
{
    glUniform1i(GetUniformLocation(Name), Value);
}

void GameEngine::Renderer::Shader::SetFloat(const std::string& Name, float Value)
{
    glUniform1f(GetUniformLocation(Name), Value);
}

void GameEngine::Renderer::Shader::SetFloat2(const std::string& Name, const glm::vec2& Value)
{
    glUniform2fv(GetUniformLocation(Name),  1, glm::value_ptr(Value));
}

void GameEngine::Renderer::Shader::SetFloat3(const std::string& Name, const glm::vec3& Value)
{
    glUniform3fv(GetUniformLocation(Name), 1, glm::value_ptr(Value));
}

void GameEngine::Renderer::Shader::SetFloat4(const std::string& Name, const glm::vec4& Value)
{
    glUniform4fv(GetUniformLocation(Name), 1, glm::value_ptr(Value));
}

void GameEngine::Renderer::Shader::SetMat4(const std::string& Name, const glm::mat4& Value)
{
    glUniformMatrix4fv(GetUniformLocation(Name), 1, GL_FALSE, glm::value_ptr(Value));
}
