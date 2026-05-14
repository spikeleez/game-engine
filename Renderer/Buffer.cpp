#include "Buffer.h"
#include <glad/glad.h>

GameEngine::Renderer::VertexBuffer::VertexBuffer(const void* Data, uint32_t Size)
{
    glCreateBuffers(1, &RendererID);
    glBindBuffer(GL_ARRAY_BUFFER, RendererID);
    glBufferData(GL_ARRAY_BUFFER, Size, Data, GL_STATIC_DRAW);
}

GameEngine::Renderer::VertexBuffer::VertexBuffer(uint32_t Size)
{
    glCreateBuffers(1, &RendererID);
    glBindBuffer(GL_ARRAY_BUFFER, RendererID);
    glBufferData(GL_ARRAY_BUFFER, Size, nullptr, GL_DYNAMIC_DRAW);
}

GameEngine::Renderer::VertexBuffer::~VertexBuffer()
{
    glDeleteBuffers(1, &RendererID);
}

void GameEngine::Renderer::VertexBuffer::Bind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, RendererID);
}

void GameEngine::Renderer::VertexBuffer::Unbind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void GameEngine::Renderer::VertexBuffer::SetData(const void* Data, uint32_t Size)
{
    glBindBuffer(GL_ARRAY_BUFFER, RendererID);
    glBufferSubData(GL_ARRAY_BUFFER, 0, Size, Data);
}

GameEngine::Renderer::IndexBuffer::IndexBuffer(const uint32_t* Indices, uint32_t Count)
{
    glCreateBuffers(1, &RendererID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, RendererID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, Count * sizeof(uint32_t), Indices, GL_STATIC_DRAW);
}

GameEngine::Renderer::IndexBuffer::~IndexBuffer()
{
    glDeleteBuffers(1, &RendererID);
}

void GameEngine::Renderer::IndexBuffer::Bind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, RendererID);
}

void GameEngine::Renderer::IndexBuffer::Unbind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
