#pragma once

#include <glm/glm.hpp>

namespace GameEngine::Renderer
{
    class Camera2D
    {
    public:
        Camera2D(float Left, float Right, float Bottom, float Top);

        void SetPosition(const glm::vec2& InPosition);
        void SetZoom(float InZoom);

        [[nodiscard]]const glm::mat4& GetViewProjection() const { return ViewProjectionMatrix; }

    private:
        void RecalculateMatrix();

        glm::mat4 ProjectionMatrix;
        glm::mat4 ViewMatrix;
        glm::mat4 ViewProjectionMatrix;

        glm::vec2 Position { 0.0f, 0.0f };
        float Zoom = 1.0f;
    };
}
