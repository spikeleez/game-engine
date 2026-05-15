#pragma once

#include "Shader.h"
#include "VertexArray.h"
#include "Camera2D.h"
#include <glm/glm.hpp>
#include <memory>

namespace GameEngine::Renderer
{
    class Renderer2D
    {
    public:
        static void Init();
        static void Shutdown();

        static void BeginScene(const Camera2D& Camera);
        static void EndScene();

        static void DrawQuad(const glm::vec2& Position, const glm::vec2& Size, const glm::vec4& Color);
        static void DrawQuadRotated(const glm::vec2& Position, const glm::vec2& Size, float Rotation, const glm::vec4& Color);
        static void DrawCircle(const glm::vec2& Center, float Radius, const glm::vec4& Color, float Thickness = 1.0f);
        static void DrawLine(const glm::vec2& Start, const glm::vec2& End, const glm::vec4& Color, float Thickness = 2.0f);
        static void DrawDashedLine(const glm::vec2& Start, const glm::vec2& End, const glm::vec4& Color, float Thickness = 2.0f, float DashLength = 20.0f, float Gap = 15.0f);

    private:
        struct SceneData
        {
            glm::mat4 ViewProjection;
        };

        static void SubmitQuad(const glm::mat4& Transform, const glm::vec4& Color);

        static SceneData* Scene;
        static std::unique_ptr<Shader> QuadShader;
        static std::unique_ptr<Shader> CircleShader;
        static std::unique_ptr<VertexArray> QuadVAO;
    };
}
