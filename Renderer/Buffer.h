#pragma once

#include <cstdint>
#include <vector>
#include <string>

namespace GameEngine::Renderer
{
    enum class ShaderDataType
    {
        Float,
        Float2,
        Float3,
        Float4
    };

    static uint32_t ShaderDataTypeSize(ShaderDataType Type)
    {
        switch (Type)
        {
            case ShaderDataType::Float:     return 4;
            case ShaderDataType::Float2:    return 8;
            case ShaderDataType::Float3:    return 12;
            case ShaderDataType::Float4:    return 16;
        }
        return 0;
    }

    struct VertexElement
    {
        std::string Name;
        enum ShaderDataType Type;
        uint32_t Size;
        uint32_t Offset = 0;
        bool bNormalized = false;

        VertexElement(ShaderDataType Type, std::string Name)
            : Name(std::move(Name))
            , Type(Type)
            , Size(ShaderDataTypeSize(Type))
        {}

        [[nodiscard]]uint32_t GetComponentCount() const
        {
            switch (Type)
            {
                case ShaderDataType::Float:     return 1;
                case ShaderDataType::Float2:    return 2;
                case ShaderDataType::Float3:    return 3;
                case ShaderDataType::Float4:    return 4;
            }
            return 0;
        }
    };

    class VertexLayout
    {
    public:
        VertexLayout() = default;
        VertexLayout(std::initializer_list<VertexElement> Elements)
            : Elements(Elements)
        {
            uint32_t Offset = 0;
            Stride = 0;
            for (auto& Element : this->Elements)
            {
                Element.Offset = Offset;
                Offset += Element.Size;
                Stride += Element.Size;
            }
        }

        [[nodiscard]]const std::vector<VertexElement>& GetElements() const { return Elements; }
        [[nodiscard]]uint32_t GetStride() const { return Stride; }

    private:
        std::vector<VertexElement> Elements;
        uint32_t Stride = 0;
    };

    class VertexBuffer
    {
    public:
        VertexBuffer(const void* Data, uint32_t Size);
        VertexBuffer(uint32_t Size); // dynamic buffer (without intial data).
        ~VertexBuffer();

        void Bind() const;
        void Unbind() const;

        void SetData(const void* Data, uint32_t Size);
        void SetLayout(const VertexLayout& NewLayout) { this->Layout = NewLayout; }

        [[nodiscard]]const VertexLayout& GetLayout() const { return Layout; }

    private:
        uint32_t RendererID = 0;
        VertexLayout Layout;
    };

    // Triangle indices.
    class IndexBuffer
    {
    public:
        IndexBuffer(const uint32_t* Indices, uint32_t Count);
        ~IndexBuffer();

        void Bind() const;
        void Unbind() const;

        [[nodiscard]]uint32_t GetCount() const { return Count; }

    private:
        uint32_t RendererID = 0;
        uint32_t Count = 0;
    };
}
