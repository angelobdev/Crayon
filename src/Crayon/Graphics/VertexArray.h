#pragma once

#include "Common.h"
#include "VertexBuffer.h"

#define INT_TO_VOID_PTR(i) (const void *)(uintptr_t)(i)

namespace Crayon
{
    class VertexArray
    {
    private:
        unsigned int m_ID;

    public:
        VertexArray();

        ~VertexArray()
        {}

        void Bind() const;

        void Unbind() const;

        void LinkBuffer(const VertexBuffer &vb);
    };
}