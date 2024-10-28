#pragma once

#include "crypch.h"

#include "Core/IndexBuffer.h"
#include "Core/OpenGL.h"
#include "Core/VertexArray.h"
#include "Core/VertexBuffer.h"

namespace Crayon::Graphics
{
    template <typename T>
    class Mesh
    {
    private:
        std::shared_ptr<Core::VertexArray> m_VertexArray;
        std::shared_ptr<Core::VertexBuffer<T>> m_VertexBuffer;
        std::shared_ptr<Core::IndexBuffer> m_IndexBuffer;

    public:
        Mesh(const std::vector<T> &vertices, const std::vector<Core::VertexLayout> &verticesLayout, const std::vector<unsigned int> &indices)
        {
            this->m_VertexArray = std::make_shared<Core::VertexArray>();
            this->m_VertexArray->Bind();

            this->m_VertexBuffer = std::make_shared<Core::VertexBuffer<T>>(vertices, verticesLayout);
            this->m_IndexBuffer = std::make_shared<Core::IndexBuffer>(indices);

            this->m_VertexArray->Unbind();
        }

        const Core::VertexArray &GetVAO() const
        {
            return *this->m_VertexArray.get();
        }

        const Core::VertexBuffer<T> &GetVBO() const
        {
            return *this->m_VertexBuffer.get();
        }

        const Core::IndexBuffer &GetIBO() const
        {
            return *this->m_IndexBuffer.get();
        }
    };
}