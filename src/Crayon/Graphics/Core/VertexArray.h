#pragma once

#include "Crayon/Graphics/Common.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Crayon/Graphics/Utils/VertexLayout.h"

namespace Crayon
{
    class VertexArray
    {
    private:
        unsigned int m_ID;

    public:

        // CONSTRUCTOR AND DESTRUCTOR

        VertexArray();

        ~VertexArray() {}

        // METHODS

        void Bind() const;

        void Unbind() const;

        void LinkBuffer(const VertexBuffer &vb, const VertexLayout &layout);

    };
}