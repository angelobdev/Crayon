#include "VertexBuffer.h"
#include "Crayon/Utilities/GLUtils.h"

namespace Crayon {
    VertexBuffer::VertexBuffer(const std::vector<float> &vertices, const std::vector<VertexLayoutElement> &VLEs) {
        // Creating buffer
        GLCall(glGenBuffers(1, &this->m_ID));
        GLCall(glBindBuffer(GL_ARRAY_BUFFER, this->m_ID));
        GLCall(glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices[0], GL_STATIC_DRAW));
        GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));

        // Setting layout elements
        this->m_Stride = 0;
        this->m_VLEs = VLEs;
        for (const auto elem: this->m_VLEs)
            this->m_Stride += GLUtils::GetSizeOfType(elem.type) * elem.count;
    }

    void VertexBuffer::Bind() const {
        GLCall(glBindBuffer(GL_ARRAY_BUFFER, this->m_ID));
    }

    void VertexBuffer::Unbind() const {
        GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
    }
} // Crayon