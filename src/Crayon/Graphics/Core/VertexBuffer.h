#pragma once

#include "OpenGL.h"

namespace Crayon::Graphics::Core
{

    struct VertexLayout
    {
        unsigned int count;
        unsigned int type;
        bool normalized = false;

        VertexLayout(unsigned int count, unsigned int type, bool normalized)
            : count(count), type(type), normalized(normalized) {}

        VertexLayout(unsigned int count, unsigned int type)
            : count(count), type(type), normalized(false) {}
    };

    template <typename T>
    class VertexBuffer
    {
    private:
        unsigned int m_ID;
        std::vector<VertexLayout> m_VerticesLayout;

    public:
        // CONSTRUCTOR & DESTRUCTOR

        VertexBuffer(const std::vector<T> &vertices, const std::vector<VertexLayout> &verticesLayout)
        {
            // Creating buffer
            GLCall(glGenBuffers(1, &this->m_ID));
            GLCall(glBindBuffer(GL_ARRAY_BUFFER, this->m_ID));
            GLCall(glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(T), &vertices[0], GL_STATIC_DRAW));

            // Calculating stride
            unsigned int offset = 0;
            unsigned int stride = 0;
            for (const auto &layout : verticesLayout)
            {
                stride += layout.count * sizeof(T);
            }

            // Linking buffer to currently bound VAO
            for (unsigned int i = 0; i < verticesLayout.size(); i++)
            {
                const auto &layout = verticesLayout[i];
                GLCall(glEnableVertexAttribArray(i));
                GLCall(glVertexAttribPointer(i, layout.count, layout.type, layout.normalized ? GL_TRUE : GL_FALSE, stride, reinterpret_cast<void *>(offset)));
                offset += layout.count * sizeof(T);
            }

            GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
        }

        ~VertexBuffer()
        {
            GLCall(glDeleteBuffers(1, &this->m_ID));
        }

        // METHODS

        void Bind() const
        {
            GLCall(glBindBuffer(GL_ARRAY_BUFFER, this->m_ID));
        }

        void Unbind() const
        {
            GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
        }

        // GETTERS AND SETTERS

        const unsigned int GetID() const { return this->m_ID; }
    };
}