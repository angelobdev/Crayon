#pragma once

#include "Crayon/Graphics/GLCommon.h"

namespace Crayon
{
    class IndexBuffer
    {
    private:
        unsigned int m_ID;
        unsigned int m_Count; // Number of indices

    public:
        // CONSTRUCTOR & DESTRUCTOR

        IndexBuffer(const std::vector<unsigned int> &indices) : m_Count((unsigned int)indices.size())
        {
            GLCall(glGenBuffers(1, &this->m_ID));
            GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->m_ID));
            GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(float), &indices[0], GL_STATIC_DRAW));
            GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
        }

        ~IndexBuffer() {}

        // METHODS

        void Bind() const
        {
            GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->m_ID));
        }

        void Unbind() const
        {
            GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
        }

        // GETTERS

        inline const unsigned int &GetCount() const { return this->m_Count; }
    };
}