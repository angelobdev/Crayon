#include "IndexBuffer.h"

namespace Crayon
{
    IndexBuffer::IndexBuffer(const std::vector<unsigned int> &indices)
        : m_Count((unsigned int)indices.size())
    {
        GLCall(glGenBuffers(1, &this->m_ID));
        GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->m_ID));
        GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(float), &indices[0], GL_STATIC_DRAW));
        GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
    }

    void IndexBuffer::Bind() const
    {
        GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->m_ID));
    }

    void IndexBuffer::Unbind() const
    {
        GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
    }
}