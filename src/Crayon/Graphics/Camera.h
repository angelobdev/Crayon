#pragma once

#include "Crayon/Graphics/GLCommon.h"

namespace Crayon
{
    struct Directions
    {
        static const glm::vec3 UP;
        static const glm::vec3 DOWN;
        static const glm::vec3 LEFT;
        static const glm::vec3 RIGHT;
        static const glm::vec3 FORWARD;
        static const glm::vec3 BACK;
    };

    const glm::vec3 Directions::UP = glm::vec3(0.0f, 1.0f, 0.0f);
    const glm::vec3 Directions::DOWN = glm::vec3(0.0f, -1.0f, 0.0f);
    const glm::vec3 Directions::LEFT = glm::vec3(-1.0f, 0.0f, 0.0f);
    const glm::vec3 Directions::RIGHT = glm::vec3(1.0f, 0.0f, 0.0f);
    const glm::vec3 Directions::FORWARD = glm::vec3(0.0f, 0.0f, -1.0f);
    const glm::vec3 Directions::BACK = glm::vec3(0.0f, 0.0f, 1.0f);

    class Camera
    {
    private:
        glm::vec3 m_Position, m_Rotation; // (X, Y, Z) (Pitch, Yaw, Roll)
        glm::vec3 m_Up, m_Front, m_Right;
        glm::mat4 m_View;

        float m_Sensitivity;
        glm::vec2 m_LastMousePos;

    public:
        Camera(const glm::vec3 &position)
            : m_Position(position),
              m_Rotation(0, 0, 0),
              m_Up(Directions::UP),
              m_Front(Directions::FORWARD),
              m_Right(Directions::RIGHT),
              m_Sensitivity(50),
              m_View(glm::lookAt(position, position + Directions::FORWARD, Directions::UP))
        {
            this->m_LastMousePos = glm::vec2(0, 0);
        }

        void Update(const float deltaTime)
        {
            // Handling Mouse
            auto newMousePos = Crayon::Input::GetCursorPosition();
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
            if (Crayon::Input::GetKeyDown(Crayon::Events::KeyCode::W))
                m_Position += m_Front * deltaTime;
            if (Crayon::Input::GetKeyDown(Crayon::Events::KeyCode::S))
                m_Position -= m_Front * deltaTime;
            if (Crayon::Input::GetKeyDown(Crayon::Events::KeyCode::D))
                m_Position += m_Right * deltaTime;
            if (Crayon::Input::GetKeyDown(Crayon::Events::KeyCode::A))
                m_Position -= m_Right * deltaTime;
            if (Crayon::Input::GetKeyDown(Crayon::Events::KeyCode::LSHIFT))
                m_Position += Directions::DOWN * deltaTime;
            if (Crayon::Input::GetKeyDown(Crayon::Events::KeyCode::SPACE))
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

        float GetSensitivity() const { return m_Sensitivity; }

        void SetSensitivity(float sensitivity) { m_Sensitivity = sensitivity; }
    };
}