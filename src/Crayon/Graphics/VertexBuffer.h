#pragma once

#include "Crayon/Graphics/GLCommon.h"

namespace Crayon
{
    class VertexBuffer
    {
    private:
        unsigned int m_ID;

    public:
        // CONSTRUCTOR & DESTRUCTOR

        VertexBuffer(const std::vector<float> &vertices)
        {
            // Creating buffer
            GLCall(glGenBuffers(1, &this->m_ID));
            GLCall(glBindBuffer(GL_ARRAY_BUFFER, this->m_ID));
            GLCall(glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices[0], GL_STATIC_DRAW));
            GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
        }

        ~VertexBuffer() {}

        // METHODS

        void Bind() const
        {
            GLCall(glBindBuffer(GL_ARRAY_BUFFER, this->m_ID));
        }

        void Unbind() const
        {
            GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
        }

        // GETTERS AND SETTERS

        const unsigned int GetID() const { return this->m_ID; }
    };
}