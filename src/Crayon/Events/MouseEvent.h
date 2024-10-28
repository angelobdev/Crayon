#pragma once

#include <GLFW/glfw3.h>

namespace Crayon:: Events
    {
        enum class MouseButton
        {
            LEFT_BUTTON = GLFW_MOUSE_BUTTON_LEFT,
            MIDDLE_BUTTON = GLFW_MOUSE_BUTTON_MIDDLE,
            RIGHT_BUTTON = GLFW_MOUSE_BUTTON_RIGHT,
        };

        enum class MouseState
        {
            Null,
            Clicked,
            Released,
        };

        struct MouseEvent
        {
        private:
            const MouseButton m_Button;
            const MouseState m_State;

        public:
            MouseEvent(MouseButton button, MouseState state)
                : m_Button(button), m_State(state) {}

            const MouseButton GetButton() const
            {
                return m_Button;
            }

            const MouseState GetState() const
            {
                return m_State;
            }
        };
    }
