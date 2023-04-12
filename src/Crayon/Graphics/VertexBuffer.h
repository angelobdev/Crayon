#pragma once

#include "Common.h"

namespace Crayon
{
    struct VertexLayoutElement // Used to retrieve the size of vertex elements and calculate stride
    {
        unsigned int count;
        unsigned int type;
        bool normalized = false;
    };

    class VertexBuffer
    {
    private:
        unsigned int m_ID;
        std::vector<VertexLayoutElement> m_VLEs; // Vertex Layout Elements
        unsigned int m_Stride;

    public:
        VertexBuffer(const std::vector<float> &vertices, const std::vector<VertexLayoutElement> &LOEs);
        ~VertexBuffer() {}

        void Bind() const;
        void Unbind() const;

        // GETTERS AND SETTERS

        const unsigned int GetID() const { return this->m_ID; }
        const std::vector<VertexLayoutElement> &GetLayoutElements() const { return this->m_VLEs; }
        const unsigned int GetStride() const { return this->m_Stride; }
    };
}