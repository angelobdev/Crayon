#pragma once

#include "crypch.h"

#include "Core/OpenGL.h"

namespace Crayon::Graphics
{
    class Light
    {
    private:
        glm::vec3 m_Position;
        glm::vec3 m_Color;

    public:
        Light()
            : m_Position(0, 100.0f, 0), m_Color(1.0f) {}

        Light(const glm::vec3 &position)
            : m_Position(position), m_Color(1.0f) {}

        Light(const glm::vec3 &position, const glm::vec3 &color)
            : m_Position(position), m_Color(color) {}

        const glm::vec3 &GetPosition() const
        {
            return m_Position;
        }

        const glm::vec3 &GetColor() const
        {
            return m_Color;
        }
    };
}