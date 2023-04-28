#include "VertexLayout.h"
#include "CommonUtils.h"

namespace Crayon
{
    VertexLayout::VertexLayout(const std::vector<VertexLayoutElement> &VLEs)
            : m_Stride(0)
    {
        for (const auto &elem: VLEs)
        {
            this->Push(elem);
        }
    }

    void VertexLayout::Push(const VertexLayoutElement &element)
    {
        this->m_VLEs.push_back(element);
        this->m_Stride += element.count * CommonUtils::GetSizeOfType(element.type);
    }

    void VertexLayout::PushAll(const std::vector<VertexLayoutElement> VLEs)
    {
        for (const auto &elem: VLEs)
        {
            this->Push(elem);
        }
    }
}