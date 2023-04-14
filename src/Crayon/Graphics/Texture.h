#pragma once

/**************************************************************************************************
 * @file JAGL/Graphics/Texture.h
 * @brief Texture class header file.
 * @details This file implements the Texture wrapper class structure.
 **************************************************************************************************
 * @author angelobdev
 * @date 02-03-2023
 ***************************************************************************************************/

#include "Common.h"

namespace Crayon
{
    class Texture
    {
    private:
        unsigned int m_ID;
        std::string m_FilePath;       // Texture file location
        unsigned char *m_LocalBuffer; // Texture buffer
        int m_Width, m_Height, m_BPP; // Texture attributes

    public:
        /// @brief Generates an OpenGL texture based on the specified image
        /// @param filePath Image file path
        Texture(const std::string &filePath);
        ~Texture();

        /// @brief Binds the current texture (you can specify a slot)
        /// @param slot *platform dependant [0-32] almost always
        void Bind(unsigned int slot = 0) const;

        /// @brief Unbinds the current texture
        void Unbind() const;

        /// @brief Returns the width of the image attached to the texture
        /// @return
        inline const int &GetWidth() const { return this->m_Width; }

        /// @brief Returns the height of the image attached to the texture
        /// @return
        inline const int &GetHeight() const { return this->m_Height; }
    };
}