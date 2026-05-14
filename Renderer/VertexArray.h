#pragma once

#include "Buffer.h"
#include <memory>
#include <vector>

namespace GameEngine::Renderer
{
    class VertexArray
    {
    public:
        VertexArray();
        ~VertexArray();

        void Bind() const;
        void Unbind() const;

        void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& VBO);
        void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& EBO);

        [[nodiscard]]const std::shared_ptr<IndexBuffer>& GetIndexBuffer() const { return IBO; }

    private:
        uint32_t RendererID = 0;
        uint32_t AttribIndex = 0;
        std::vector<std::shared_ptr<VertexBuffer>> VertexBuffers;
        std::shared_ptr<IndexBuffer> IBO;
    };
}
