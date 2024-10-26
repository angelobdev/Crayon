#pragma once

#include "Crayon/Graphics/GLCommon.h"

#include "IndexBuffer.h"
#include "VertexBuffer.h"

namespace Crayon
{
    class VertexArray
    {
    private:
        unsigned int m_ID;

    public:
        // CONSTRUCTOR AND DESTRUCTOR

        VertexArray()
        {
            GLCall(glGenVertexArrays(1, &this->m_ID));
        }

        ~VertexArray() {}

        // METHODS

        void Bind() const
        {
            GLCall(glBindVertexArray(this->m_ID));
        }

        void Unbind() const
        {
            GLCall(glBindVertexArray(0));
        }
    };
}