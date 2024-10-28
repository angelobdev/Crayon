#pragma once

#include "OpenGL.h"

namespace Crayon::Graphics::Core
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

        ~VertexArray()
        {
            GLCall(glDeleteVertexArrays(1, &this->m_ID));
        }

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