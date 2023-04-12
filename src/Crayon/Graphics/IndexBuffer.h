#pragma once

#include "Common.h"

namespace Crayon
{
    class IndexBuffer
    {
    private:
        unsigned int m_ID;
        unsigned int m_Count; // Number of indices

    public:
        IndexBuffer(const std::vector<unsigned int> &indices);
        ~IndexBuffer() {}

        void Bind() const;
        void Unbind() const;

        inline const unsigned int &GetCount() const { return this->m_Count; }
    };

}
