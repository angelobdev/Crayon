#include "VertexBuffer.h"
#include "Crayon/Graphics/Utils/CommonUtils.h"

namespace Crayon
{
    VertexBuffer::VertexBuffer(const std::vector<float> &vertices)
    {
        // Creating buffer
        GLCall(glGenBuffers(1, &this->m_ID));
        GLCall(glBindBuffer(GL_ARRAY_BUFFER, this->m_ID));
        GLCall(glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices[0], GL_STATIC_DRAW));
        GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
    }

    void VertexBuffer::Bind() const
    {
        GLCall(glBindBuffer(GL_ARRAY_BUFFER, this->m_ID));
    }

    void VertexBuffer::Unbind() const
    {
        GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
    }
}