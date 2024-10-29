#pragma once

#include "Core/OpenGL.h"

namespace Crayon::Graphics
{
    class Material
    {
    private:
        glm::vec3 m_Color;
        float ambient, diffuse, specular;

    public:
        Material()
            : m_Color(1.0f), ambient(0.5f), diffuse(0.5f), specular(0.5f) {}

        Material(const glm::vec3 &color)
            : m_Color(color), ambient(0.5f), diffuse(0.5f), specular(0.5f) {}

        Material(const glm::vec3 &color, float ambient, float diffuse, float specular)
            : m_Color(color), ambient(ambient), diffuse(diffuse), specular(specular) {}

        const glm::vec3 &GetColor() const
        {
            return m_Color;
        }

        float GetAmbient() const
        {
            return ambient;
        }

        float GetDiffuse() const
        {
            return diffuse;
        }

        float GetSpecular() const
        {
            return specular;
        }
    };
}