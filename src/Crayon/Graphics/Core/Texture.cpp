#include "Texture.h"

#define STB_IMAGE_IMPLEMENTATION

#include <stb_image.h>

namespace Crayon
{
    Texture::Texture(const std::string &filePath)
            : m_ID(0), m_FilePath(filePath), m_LocalBuffer(NULL),
              m_Width(0), m_Height(0), m_BPP(0)
    {
        // Creating OpenGL Texture Buffer
        GLCall(glGenTextures(1, &this->m_ID));
        GLCall(glBindTexture(GL_TEXTURE_2D, this->m_ID));

        // Setting Texture Buffer Parameters
        GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
        GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));

        // Loading the image
        stbi_set_flip_vertically_on_load(1);
        this->m_LocalBuffer = stbi_load(filePath.c_str(), &this->m_Width, &this->m_Height, &this->m_BPP, 4);

        // Setting Texture Data
        spdlog::debug("Trying to load texture from: {}", this->m_FilePath);
        if (this->m_LocalBuffer)
        {
            GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, this->m_Width, this->m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE,
                                this->m_LocalBuffer));
            glGenerateMipmap(GL_TEXTURE_2D);
            stbi_image_free(this->m_LocalBuffer);
            spdlog::debug("Texture loaded correctly!");
        } else
        {
            spdlog::error("Failed to load texture: {}", stbi_failure_reason());
        }

        GLCall(glBindTexture(GL_TEXTURE_2D, 0));
    }

    Texture::~Texture()
    {
        GLCall(glDeleteTextures(1, &this->m_ID));
    }

    void Texture::Bind(uint slot) const
    {
        GLCall(glActiveTexture(GL_TEXTURE0 + slot));
        GLCall(glBindTexture(GL_TEXTURE_2D, this->m_ID));
    }

    void Texture::Unbind() const
    {
        GLCall(glBindTexture(GL_TEXTURE_2D, 0));
    }
}