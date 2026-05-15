#include "Renderer2D.h"
#include <glad/glad.h>
#include <glm/ext/matrix_transform.hpp>

namespace GameEngine::Renderer
{
    Renderer2D::SceneData* Renderer2D::Scene = nullptr;
    std::unique_ptr<Shader> Renderer2D::QuadShader = nullptr;
    std::unique_ptr<Shader> Renderer2D::CircleShader = nullptr;
    std::unique_ptr<VertexArray> Renderer2D::QuadVAO = nullptr;

    static const char* VertexSrc = R"(
        #version 460 core
        layout(location = 0) in vec3 aPosition;

        uniform mat4 uViewProjection;
        uniform mat4 uTransform;

        void main()
        {
            gl_Position = uViewProjection * uTransform * vec4(aPosition, 1.0);
        }
    )";

    static const char* FragmentSrc = R"(
        #version 460 core
        out vec4 FragColor;

        uniform vec4 uColor;

        void main()
        {
            FragColor = uColor;
        }
    )";

    static const char* CircleVertSrc = R"(
        #version 460 core
        layout(location = 0) in vec3 aPosition;

        uniform mat4 uViewProjection;
        uniform mat4 uTransform;

        out vec2 vLocalPos;

        void main()
        {
            vLocalPos   = aPosition.xy;
            gl_Position = uViewProjection * uTransform * vec4(aPosition, 1.0);
        }
    )";

    static const char* CircleFragSrc = R"(
        #version 460 core

        in  vec2 vLocalPos;
        out vec4 FragColor;

        uniform vec4  uColor;
        uniform float uThickness;

        void main()
        {
            float Dist  = length(vLocalPos);
            float Fade  = 0.004;

            float Alpha = smoothstep(0.5, 0.5 - Fade, Dist);
                  Alpha *= smoothstep(0.5 - uThickness,
                                      0.5 - uThickness + Fade, Dist);

            if (Alpha <= 0.0) discard;
            FragColor = vec4(uColor.rgb, uColor.a * Alpha);
        }
    )";
}

void GameEngine::Renderer::Renderer2D::Init()
{
    Scene = new SceneData();

    float Vertices[] = {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.5f,  0.5f, 0.0f,
        -0.5f,  0.5f, 0.0f
    };

    uint32_t Indices[] = { 0, 1, 2,  2, 3, 0 };

    QuadVAO = std::make_unique<VertexArray>();

    const auto VBO = std::make_shared<VertexBuffer>(Vertices, sizeof(Vertices));
    VBO->SetLayout({ { ShaderDataType::Float3, "aPosition" } });
    QuadVAO->AddVertexBuffer(VBO);

    const auto EBO = std::make_shared<IndexBuffer>(Indices, 6);
    QuadVAO->SetIndexBuffer(EBO);

    QuadShader = std::make_unique<Shader>(VertexSrc, FragmentSrc);
    CircleShader = std::make_unique<Shader>(CircleVertSrc, CircleFragSrc);
}

void GameEngine::Renderer::Renderer2D::Shutdown()
{
    delete Scene;
}

void GameEngine::Renderer::Renderer2D::BeginScene(const Camera2D& Camera)
{
    Scene->ViewProjection = Camera.GetViewProjection();
}

void GameEngine::Renderer::Renderer2D::EndScene()
{
    // do nothing...
}

void GameEngine::Renderer::Renderer2D::SubmitQuad(const glm::mat4& Transform, const glm::vec4& Color)
{
    QuadShader->Bind();
    QuadShader->SetMat4("uViewProjection", Scene->ViewProjection);
    QuadShader->SetMat4("uTransform", Transform);
    QuadShader->SetFloat4("uColor", Color);

    QuadVAO->Bind();
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}

void GameEngine::Renderer::Renderer2D::DrawQuad(const glm::vec2& Position, const glm::vec2& Size, const glm::vec4& Color)
{
    const glm::mat4 Transform = glm::translate(glm::mat4(1.0f), glm::vec3(Position, 0.0f))
        * glm::scale(glm::mat4(1.0f), glm::vec3(Size, 1.0f));

    SubmitQuad(Transform, Color);
}

void GameEngine::Renderer::Renderer2D::DrawQuadRotated(const glm::vec2& Position, const glm::vec2& Size, float Rotation, const glm::vec4& Color)
{
    const glm::mat4 Transform = glm::translate(glm::mat4(1.0f), glm::vec3(Position, 0.0f))
        * glm::rotate(glm::mat4(1.0f), Rotation, glm::vec3(0, 0, 1))
        * glm::scale(glm::mat4(1.0f), glm::vec3(Size, 1.0f));

    SubmitQuad(Transform, Color);
}

void GameEngine::Renderer::Renderer2D::DrawCircle(const glm::vec2& Center, float Radius, const glm::vec4& Color, float Thickness)
{
    const float D = Radius * 2.0f;
    const glm::mat4 T = glm::translate(glm::mat4(1.0f), glm::vec3(Center, 0.0f))
        * glm::scale(glm::mat4(1.0f), glm::vec3(D, D, 1.0f));

    CircleShader->Bind();
    CircleShader->SetMat4("uViewProjection", Scene->ViewProjection);
    CircleShader->SetMat4("uTransform", T);
    CircleShader->SetFloat4("uColor", Color);
    CircleShader->SetFloat("uThickness", Thickness);

    QuadVAO->Bind();
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}

void GameEngine::Renderer::Renderer2D::DrawLine(const glm::vec2& Start, const glm::vec2& End, const glm::vec4& Color, float Thickness)
{
    const glm::vec2 Dir = End - Start;
    const float Length = glm::length(Dir);
    const float Angle  = glm::atan(Dir.y, Dir.x);
    const glm::vec2 Center = (Start + End) * 0.5f;

    const glm::mat4 T = glm::translate(glm::mat4(1.0f), glm::vec3(Center, 0.0f))
        * glm::rotate(glm::mat4(1.0f), Angle, glm::vec3(0, 0, 1))
        * glm::scale(glm::mat4(1.0f), glm::vec3(Length, Thickness, 1.0f));

    SubmitQuad(T, Color);
}

void GameEngine::Renderer::Renderer2D::DrawDashedLine(const glm::vec2& Start, const glm::vec2& End, const glm::vec4& Color, float Thickness, float DashLength, float Gap)
{
    const glm::vec2 Dir = End - Start;
    const float Total = glm::length(Dir);
    const glm::vec2 UnitDir  = Dir / Total;
    const float Step = DashLength + Gap;
    float Traveled = 0.0f;

    while (Traveled + DashLength <= Total)
    {
        glm::vec2 DashStart = Start + UnitDir * Traveled;
        glm::vec2 DashEnd = Start + UnitDir * (Traveled + DashLength);
        DrawLine(DashStart, DashEnd, Color, Thickness);
        Traveled += Step;
    }
}
