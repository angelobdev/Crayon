#pragma once

/**************************************************************************************************
 * @file JAGL/Graphics/VertexBuffer.h
 * @brief VertexBuffer class header file.
 * @details This file implements the VertexBuffer wrapper class structure.
 **************************************************************************************************
 * @author angelobdev
 * @date 01-27-2023
 ***************************************************************************************************/

#include "Common.h"

namespace Crayon
{
    struct VertexLayoutElement // Used to retrieve the size of vertex elements and calculate stride
    {
        unsigned int count;
        unsigned int type;
        bool normalized = false;
    };

    /// @brief GL_ARRAY_BUFFER wrapper class.
    class VertexBuffer
    {
    private:
        unsigned int m_ID;
        std::vector<VertexLayoutElement> m_VLEs; // Vertex Layout Elements
        unsigned int m_Stride;

    public:
        /// @brief Generates the VertexBuffer based on a std::vector of float values
        /// @param vertices Array of indices
        VertexBuffer(const std::vector<float> &vertices, const std::vector<VertexLayoutElement> &LOEs);
        ~VertexBuffer() {}

        /// @brief Binds the current VertexBuffer
        void Bind() const;

        /// @brief Unbinds the current VertexBuffer
        void Unbind() const;

        // GETTERS AND SETTERS

        const unsigned int GetID() const { return this->m_ID; }
        const std::vector<VertexLayoutElement> &GetLayoutElements() const { return this->m_VLEs; }
        const unsigned int GetStride() const { return this->m_Stride; }
    };
}