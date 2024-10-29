#pragma once

#include "OpenGL.h"
#include "VertexLayout.h"

namespace Crayon::Graphics::Core
{
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
            unsigned int stride = 0;
            for (const auto &layout : verticesLayout)
            {
                stride += layout.count * GetSizeFromType(layout.type);
            }

            // Linking buffer to currently bound VAO
            unsigned int offset = 0;
            for (unsigned int i = 0; i < verticesLayout.size(); i++)
            {
                const auto &layout = verticesLayout[i];
                GLCall(glEnableVertexAttribArray(i));
                GLCall(glVertexAttribPointer(i, layout.count, layout.type, layout.normalized ? GL_TRUE : GL_FALSE, stride, reinterpret_cast<void *>(offset)));
                offset += layout.count * GetSizeFromType(layout.type);
            }
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

    private:
        static int GetSizeFromType(GLenum type)
        {
            switch (type)
            {
            case GL_FLOAT:
                return sizeof(float);
            case GL_INT:
                return sizeof(int);
            case GL_UNSIGNED_INT:
                return sizeof(unsigned int);
            case GL_DOUBLE:
                return sizeof(double);
            case GL_BYTE:
                return sizeof(char);
            case GL_UNSIGNED_BYTE:
                return sizeof(unsigned char);
            case GL_SHORT:
                return sizeof(short);
            case GL_UNSIGNED_SHORT:
                return sizeof(unsigned short);
            default:
                CRAYON_CORE_FATAL("Unidentified GLenum code: {}", type);
                return -1;
            }
        }
    };
}