#pragma once

#include "Crayon/Graphics/GLCommon.h"
#include "Crayon/Graphics/Utils/CommonUtils.h"
#include "Crayon/Graphics/Utils/VertexLayout.h"

#include "IndexBuffer.h"
#include "VertexBuffer.h"

namespace Crayon
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

        ~VertexArray() {}

        // METHODS

        void Bind() const
        {
            GLCall(glBindVertexArray(this->m_ID));
        }

        void Unbind() const
        {
            GLCall(glBindVertexArray(0));
        }

        void LinkBuffer(const VertexBuffer &vb, const VertexLayout &layout)
        {
            this->Bind();
            vb.Bind();

            const auto &elements = layout.GetLayoutElements();

            unsigned int offset = 0;
            for (unsigned int i = 0; i < elements.size(); i++)
            {
                const auto &elem = elements[i];

                spdlog::debug("Element: {} {} {}", elem.type, elem.count, elem.normalized);

                GLCall(glEnableVertexAttribArray(i));
                GLCall(glVertexAttribPointer(
                    i,
                    elem.count,
                    elem.type,
                    elem.normalized ? GL_TRUE : GL_FALSE,
                    layout.GetStride(),
                    INT_TO_VOID_PTR(offset)));
                offset += CommonUtils::GetSizeOfType(elem.type) * elem.count;
            }

            vb.Unbind();
            this->Unbind();
        }
    };
}