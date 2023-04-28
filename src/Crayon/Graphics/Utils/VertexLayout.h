#pragma once

namespace Crayon
{
    struct VertexLayoutElement // Used to retrieve the size of vertex elements and calculate stride
    {
        unsigned int count;
        unsigned int type;
        bool normalized = false;

        VertexLayoutElement(unsigned int count, unsigned int type, bool normalized)
                : count(count), type(type), normalized(normalized) {}

        VertexLayoutElement(unsigned int count, unsigned int type)
                : count(count), type(type), normalized(false) {}
    };

    class VertexLayout
    {
    private:
        std::vector<VertexLayoutElement> m_VLEs;
        unsigned int m_Stride;

    public:

        // CONSTRUCTOR AND DESTRUCTOR

        VertexLayout(const std::vector<VertexLayoutElement> &VLEs);

        ~VertexLayout() {}

        // METHODS

        void Push(const VertexLayoutElement &element);

        void PushAll(const std::vector<VertexLayoutElement> VLEs);

        // GETTERS AND SETTERS

        const std::vector<VertexLayoutElement> &GetLayoutElements() const { return this->m_VLEs; }

        const unsigned int GetStride() const { return this->m_Stride; }
    };
}
