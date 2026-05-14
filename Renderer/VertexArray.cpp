#include "VertexArray.h"

#include <glad/glad.h>

GameEngine::Renderer::VertexArray::VertexArray()
{
    glCreateVertexArrays(1, &RendererID);
}

GameEngine::Renderer::VertexArray::~VertexArray()
{
    glDeleteVertexArrays(1, &RendererID);
}

void GameEngine::Renderer::VertexArray::Bind() const
{
    glBindVertexArray(RendererID);
}

void GameEngine::Renderer::VertexArray::Unbind() const
{
    glBindVertexArray(0);
}

void GameEngine::Renderer::VertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer>& VBO)
{
    glBindVertexArray(RendererID);
    VBO->Bind();

    const auto& Layout = VBO->GetLayout();
    for (const auto& Element : Layout.GetElements())
    {
        glEnableVertexAttribArray(AttribIndex);
        glVertexAttribPointer(
            AttribIndex,
            Element.GetComponentCount(),
            GL_FLOAT,
            Element.bNormalized ? GL_TRUE : GL_FALSE,
            Layout.GetStride(),
            (const void*)(uintptr_t)Element.Offset
        );
        AttribIndex++;
    }

    VertexBuffers.push_back(VBO);
}

void GameEngine::Renderer::VertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer>& EBO)
{
    glBindVertexArray(RendererID);
    EBO->Bind();
    IBO = EBO;
}
