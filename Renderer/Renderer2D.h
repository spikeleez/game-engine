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

    private:
        struct SceneData
        {
            glm::mat4 ViewProjection;
        };

        static SceneData* Scene;
        static std::unique_ptr<Shader> QuadShader;
        static std::unique_ptr<VertexArray> QuadVAO;
    };
}
