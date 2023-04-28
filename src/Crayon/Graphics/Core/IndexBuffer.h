#pragma once

#include "Crayon/Graphics/Common.h"

namespace Crayon
{
    class IndexBuffer
    {
    private:
        unsigned int m_ID;
        unsigned int m_Count; // Number of indices

    public:
        // CONSTRUCTOR & DESTRUCTOR

        IndexBuffer(const std::vector<unsigned int> &indices);

        ~IndexBuffer() {}

        // METHODS

        void Bind() const;

        void Unbind() const;

        // GETTERS

        inline const unsigned int &GetCount() const { return this->m_Count; }
    };
}