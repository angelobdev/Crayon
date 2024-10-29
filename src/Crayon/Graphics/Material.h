#pragma once

#include "Core/OpenGL.h"

namespace Crayon::Graphics
{
    class Material
    {
    private:
        glm::vec3 m_Color;
        glm::vec3 m_Ambient, m_Diffuse, m_Specular;
        float m_Shininess;

    public:
        Material(const glm::vec3 &color,
                 const glm::vec3 &ambient = glm::vec3(0.1f),
                 const glm::vec3 &diffuse = glm::vec3(0.5f),
                 const glm::vec3 &specular = glm::vec3(0.5f),
                 float shininess = 32.0f)
            : m_Color(color), m_Ambient(ambient), m_Diffuse(diffuse), m_Specular(specular), m_Shininess(shininess) {}

        glm::vec3 GetColor() const { return m_Color; }
        glm::vec3 GetAmbient() const { return m_Ambient; }
        glm::vec3 GetDiffuse() const { return m_Diffuse; }
        glm::vec3 GetSpecular() const { return m_Specular; }
        float GetShininess() const { return m_Shininess; }
    };
}