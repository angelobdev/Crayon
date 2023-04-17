#pragma once

#include "Crayon/Graphics/Common.h"

namespace Crayon
{
    class VertexBuffer
    {
    private:
        unsigned int m_ID;

    public:

        // CONSTRUCTOR & DESTRUCTOR

        VertexBuffer(const std::vector<float> &vertices);

        ~VertexBuffer() {}

        // METHODS

        void Bind() const;

        void Unbind() const;

        // GETTERS AND SETTERS

        const unsigned int GetID() const { return this->m_ID; }
    };
}