#include "Camera2D.h"
#include <glm/gtc/matrix_transform.hpp>

GameEngine::Renderer::Camera2D::Camera2D(float Left, float Right, float Bottom, float Top)
{
    ProjectionMatrix = glm::ortho(Left, Right, Bottom, Top, -1.0f, 1.0f);
    ViewMatrix = glm::mat4(1.0f);
    RecalculateMatrix();
}

void GameEngine::Renderer::Camera2D::SetPosition(const glm::vec2& InPosition)
{
    Position = InPosition;
    RecalculateMatrix();
}

void GameEngine::Renderer::Camera2D::SetZoom(float InZoom)
{
    Zoom = InZoom;
    RecalculateMatrix();
}

void GameEngine::Renderer::Camera2D::RecalculateMatrix()
{
    const glm::mat4 Transform = glm::translate(glm::mat4(1.0f), glm::vec3(Position, 0.0f))
        * glm::scale(glm::mat4(1.0f), glm::vec3(Zoom, Zoom, 1.0f));

    ViewMatrix = glm::inverse(Transform);
    ViewProjectionMatrix = ProjectionMatrix * ViewMatrix;
}
