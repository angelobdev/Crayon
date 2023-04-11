#pragma once

#include "Event.h"

namespace Crayon
{
    // MOUSE BUTTON EVENT CLASS
    enum class MouseButton
    {
        Null, Left, Middle, Right
    };

    enum class MouseButtonState
    {
        Null, Pressed, Released
    };

    class MouseButtonEvent : public Event
    {
    private:
        MouseButton m_Button;
        MouseButtonState m_ButtonState;

    public:
        MouseButtonEvent(MouseButton button, MouseButtonState state) : m_Button(button),
                                                                       m_ButtonState(state) { m_IsNull = false; }

        MouseButton GetButton() const { return m_Button; }

        MouseButtonState GetButtonState() const { return m_ButtonState; }

        // Override
        std::string GetName() const override
        {
            std::string name = "Mouse Button Event: ";

            name.append("Button: ");
            switch (m_Button)
            {
                case MouseButton::Left:
                    name.append("Left");
                    break;
                case MouseButton::Middle:
                    name.append("Middle");
                    break;
                case MouseButton::Right:
                    name.append("Right");
                    break;
                case MouseButton::Null:
                    break;
            }

            name.append("State: ");
            switch (m_ButtonState)
            {
                case MouseButtonState::Pressed:
                    name.append("Pressed");
                    break;
                case MouseButtonState::Released:
                    name.append("Released");
                    break;
                case MouseButtonState::Null:
                    break;
            }

            return name;
        }
    };

    // MOUSE MOVED EVENT CLASS
    class MouseMovedEvent : public Event
    {
    private:
        double m_MouseX, m_MouseY;

    public:
        MouseMovedEvent(double x, double y) : m_MouseX(x), m_MouseY(y) { m_IsNull = false; }

        double GetX() const { return m_MouseX; }

        double GetY() const { return m_MouseY; }

        // Override
        std::string GetName() const override
        {
            std::string name = "Mouse Moved Event - ";
            name.append("X: ").append(std::to_string(m_MouseX))
                    .append("Y: ").append(std::to_string(m_MouseY));

            return name;
        }
    };
}