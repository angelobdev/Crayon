#include "VertexArray.h"
#include "Crayon/Utilities/GLUtils.h"

namespace Crayon
{
    VertexArray::VertexArray()
            : m_IndicesArray()
    {
        GLCall(glGenVertexArrays(1, &this->m_ID));
    }

    void VertexArray::Bind() const
    {
        GLCall(glBindVertexArray(this->m_ID));
    }

    void VertexArray::Unbind() const
    {
        GLCall(glBindVertexArray(0));
    }

    void VertexArray::LinkBuffer(const VertexBuffer &vb, const std::vector<IndexBuffer> &ibs)
    {
        this->Bind();
        vb.Bind();

        const auto &elements = vb.GetLayoutElements(); // Retrieving list of elements

        unsigned int offset = 0;
        for (unsigned int i = 0; i < elements.size(); i++)
        {
            const auto &elem = elements[i];
            GLCall(glEnableVertexAttribArray(i));
            GLCall(glVertexAttribPointer(
                    i,
                    elem.count,
                    elem.type,
                    elem.normalized ? GL_TRUE : GL_FALSE,
                    vb.GetStride(),
                    INT_TO_VOID_PTR(offset)));
            offset += GLUtils::GetSizeOfType(elem.type) * elem.count;
        }

        vb.Unbind();
        this->Unbind();

        this->m_IndicesArray = ibs;
    }
}