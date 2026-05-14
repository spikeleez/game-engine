#include "Renderer2D.h"
#include <glad/glad.h>
#include <glm/ext/matrix_transform.hpp>

namespace GameEngine::Renderer
{
    Renderer2D::SceneData* Renderer2D::Scene = nullptr;
    std::unique_ptr<Shader> Renderer2D::QuadShader = nullptr;
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

void GameEngine::Renderer::Renderer2D::DrawQuad(const glm::vec2& Position, const glm::vec2& Size, const glm::vec4& Color)
{
    const glm::mat4 Transform = glm::translate(glm::mat4(1.0f), glm::vec3(Position, 0.0f))
        * glm::scale(glm::mat4(1.0f), glm::vec3(Size, 1.0f));

    QuadShader->Bind();
    QuadShader->SetMat4("uViewProjection", Scene->ViewProjection);
    QuadShader->SetMat4("uTransform", Transform);
    QuadShader->SetFloat4("uColor", Color);

    QuadVAO->Bind();
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}
