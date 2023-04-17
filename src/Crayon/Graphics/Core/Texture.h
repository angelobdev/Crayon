#pragma once

#include "Crayon/Graphics/Common.h"

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
        // CONSTRUCTOR & DESTRUCTOR

        Texture(const std::string &filePath);

        ~Texture();

        // METHODS

        void Bind(unsigned int slot = 0) const;

        void Unbind() const;

        // GETTERS

        inline const int &GetWidth() const { return this->m_Width; }

        inline const int &GetHeight() const { return this->m_Height; }
    };
}