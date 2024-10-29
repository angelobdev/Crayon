#pragma once

#include "crypch.h"

#include "Core/IndexBuffer.h"
#include "Core/Texture.h"
#include "Core/VertexArray.h"
#include "Core/VertexBuffer.h"
#include "Vertex.h"

namespace Crayon::Graphics
{
    class Mesh
    {
    private:
        Core::VertexArray m_VertexArray;
        Core::VertexBuffer<Vertex> m_VertexBuffer;
        Core::IndexBuffer m_IndexBuffer;
        Core::Texture m_Texture;

    public:
        Mesh(const std::vector<Vertex> &vertices, const std::vector<unsigned int> &indices, const std::string &texturePath)
            : m_VertexArray(), m_VertexBuffer(vertices, VERTEX_LAYOUT), m_IndexBuffer(indices), m_Texture(texturePath)
        {
        }

        const Core::VertexArray &GetVAO() const { return this->m_VertexArray; }
        const Core::VertexBuffer<Vertex> &GetVBO() const { return this->m_VertexBuffer; }
        const Core::IndexBuffer &GetIBO() const { return this->m_IndexBuffer; }
        const Core::Texture &GetTexture() const { return this->m_Texture; }
    };
}