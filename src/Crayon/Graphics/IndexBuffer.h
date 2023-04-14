#pragma once

/**************************************************************************************************
 * @file JAGL/Graphics/IndexBuffer.h
 * @brief IndexBuffer class header file.
 * @details This file implements the IndexBuffer wrapper class structure.
 **************************************************************************************************
 * @author angelobdev
 * @date 01-27-2023
 ***************************************************************************************************/

#include "Common.h"

namespace Crayon
{

    /// @brief GL_ELEMENT_ARRAY_BUFFER wrapper class.
    class IndexBuffer
    {
    private:
        unsigned int m_ID;
        unsigned int m_Count; // Number of indices

    public:
        /// @brief Generates the IndexBuffer based on a std::vector of unsigned int values
        /// @param indices Array of indices
        IndexBuffer(const std::vector<unsigned int> &indices);

        ~IndexBuffer() {}

        /// @brief Binds the current IndexBuffer
        void Bind() const;

        /// @brief Unbinds the current IndexBuffer
        void Unbind() const;

        /// @brief Returns the number of indices
        /// @return Number of indices of the current IndexBuffer
        inline const unsigned int &GetCount() const { return this->m_Count; }
    };
}