#pragma once

#include "Core/OpenGL.h"
#include "Core/VertexLayout.h"

namespace Crayon::Graphics
{
    static const std::vector<VertexLayout> VERTEX_LAYOUT = {
        {3, GL_FLOAT}, // position
        {3, GL_FLOAT}, // normal
        {2, GL_FLOAT}, // texture coords
    };

    class Vertex
    {
    private:
        glm::vec3 m_Position;
        glm::vec3 m_Normal;
        glm::vec2 m_TextureCoords;

    public:
        Vertex(const glm::vec3 &position, const glm::vec3 &normal = glm::vec3(0.0f), const glm::vec2 &textureCoords = glm::vec3(0.0f))
            : m_Position(position), m_Normal(normal), m_TextureCoords(textureCoords) {}

        const glm::vec3 &GetPosition() const
        {
            return m_Position;
        }

        const glm::vec3 &GetNormal() const
        {
            return m_Normal;
        }

        const glm::vec2 &GetTextureCoords() const
        {
            return m_TextureCoords;
        }
    };
}