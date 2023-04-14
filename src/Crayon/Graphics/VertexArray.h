#pragma once

/**************************************************************************************************
 * @file JAGL/Graphics/VertexArray.h
 * @brief VertexArray class header file.
 * @details This file implements the VertexArray wrapper class structure.
 **************************************************************************************************
 * @author angelobdev
 * @date 01-27-2023
 ***************************************************************************************************/

#include "Common.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"

namespace Crayon
{
    /// @brief OpenGL vertex array wrapper class
    class VertexArray
    {
    private:
        unsigned int m_ID;
        std::vector<IndexBuffer> m_IndicesArray; // This allows to render more complex objects (MAY BE REMOVED)

    public:
        /// @brief Generates a new VertexArray
        VertexArray();

        ~VertexArray() {}

        /// @brief Binds the current VertexArray
        void Bind() const;

        /// @brief Unbinds the current VertexArray
        void Unbind() const;

        /// @brief Links the specified buffer following the specified layout
        /// @param buffer Vertex Buffer to bind
        /// @param layout Vertex Layout
        void LinkBuffer(const VertexBuffer &vb, const std::vector<IndexBuffer> &ibs);

        // GETTERS
        const std::vector<IndexBuffer> &GetIndicesArray() const { return this->m_IndicesArray; }
    };
}