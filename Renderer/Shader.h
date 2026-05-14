#pragma once

#include <string>
#include <glm/glm.hpp>

namespace GameEngine::Renderer
{
    class Shader
    {
    public:
        Shader(const std::string& VertexSrc, const std::string& FragmentSrc);
        ~Shader();

        void Bind() const;
        void Unbind() const;

        void SetInt(const std::string& Name, int Value);
        void SetFloat(const std::string& Name, float Value);
        void SetFloat2(const std::string& Name, const glm::vec2& Value);
        void SetFloat3(const std::string& Name, const glm::vec3& Value);
        void SetFloat4(const std::string& Name, const glm::vec4& Value);
        void SetMat4(const std::string& Name, const glm::mat4& Value);

    private:
        uint32_t Compile(uint32_t Type, const std::string& Src);
        int GetUniformLocation(const std::string& Name) const;

        uint32_t RendererID = 0;
    };

}
