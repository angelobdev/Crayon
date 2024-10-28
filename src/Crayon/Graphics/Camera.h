#pragma once

#include "Core/OpenGL.h"
#include "Directions.h"

namespace Crayon::Graphics
{
    class Camera
    {
    private:
        glm::vec3 m_Position, m_Rotation; // (X, Y, Z) (Pitch, Yaw, Roll)
        glm::vec3 m_Up, m_Front, m_Right;
        glm::mat4 m_View, m_Projection;

        float m_Sensitivity;
        glm::vec2 m_LastMousePos;

    public:
        Camera(const glm::vec3 &position, const glm::vec3 &rotation, const Crayon::Core::Window &window)
            : m_Position(position),
              m_Rotation(rotation),
              m_Up(Directions::UP),
              m_Front(Directions::FORWARD),
              m_Right(Directions::RIGHT),
              m_Sensitivity(50),
              m_View(glm::lookAt(position, position + Directions::FORWARD, Directions::UP)),
              m_Projection(
                  glm::perspective(
                      glm::radians(70.0f),
                      window.GetAspectRatio(),
                      0.1f,
                      100.0f))

        {
            this->m_LastMousePos = Crayon::Core::Input::GetCursorPosition();
        }

        void Update(const float deltaTime)
        {
            // Handling Mouse
            auto newMousePos = Crayon::Core::Input::GetCursorPosition();
            auto mouseOffset = (newMousePos - this->m_LastMousePos) * (deltaTime * this->m_Sensitivity);

            // Yaw
            m_Rotation.y += mouseOffset.x;

            // Pitch
            m_Rotation.x -= mouseOffset.y;
            if (m_Rotation.x > 89.0f)
                m_Rotation.x = 89.0f;
            if (m_Rotation.x < -89.0f)
                m_Rotation.x = -89.0f;

            // Rotating

            glm::vec3 direction;
            direction.x = cos(glm::radians(m_Rotation.y)) * cos(glm::radians(m_Rotation.x));
            direction.y = sin(glm::radians(m_Rotation.x));
            direction.z = sin(glm::radians(m_Rotation.y)) * cos(glm::radians(m_Rotation.x));
            m_Front = glm::normalize(direction);
            m_Right = glm::cross(m_Front, m_Up);

            this->m_LastMousePos = newMousePos;

            // Handling Keyboard
            if (Crayon::Core::Input::GetKeyDown(Crayon::Events::KeyCode::W))
                m_Position += m_Front * deltaTime;
            if (Crayon::Core::Input::GetKeyDown(Crayon::Events::KeyCode::S))
                m_Position -= m_Front * deltaTime;
            if (Crayon::Core::Input::GetKeyDown(Crayon::Events::KeyCode::D))
                m_Position += m_Right * deltaTime;
            if (Crayon::Core::Input::GetKeyDown(Crayon::Events::KeyCode::A))
                m_Position -= m_Right * deltaTime;
            if (Crayon::Core::Input::GetKeyDown(Crayon::Events::KeyCode::LSHIFT))
                m_Position += Directions::DOWN * deltaTime;
            if (Crayon::Core::Input::GetKeyDown(Crayon::Events::KeyCode::SPACE))
                m_Position += Directions::UP * deltaTime;

            // Updating matrix
            m_View = glm::lookAt(m_Position, m_Position + m_Front, m_Up);
        }

        // GETTERS & SETTERS

        const glm::vec3 &GetPosition() const { return m_Position; }
        const glm::vec3 &GetRotation() const { return m_Rotation; }

        const glm::vec3 &GetUp() const { return m_Up; }
        const glm::vec3 &GetFront() const { return m_Front; }
        const glm::vec3 &GetRight() const { return m_Right; }

        const glm::mat4 &GetView() const { return m_View; }
        const glm::mat4 &GetProjection() const { return m_Projection; }

        float GetSensitivity() const { return m_Sensitivity; }

        void SetSensitivity(float sensitivity) { m_Sensitivity = sensitivity; }
    };
}