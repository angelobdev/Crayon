#pragma once

#include "Event.h"

namespace Crayon
{
    using Key = int;
    enum class KeyState
    {
        Null = BIT(1),
        Touched = BIT(2),
        Pressed = BIT(3),
        Released = BIT(4)
                //TODO: CHECK
    };

    class KeyEvent : public Event
    {
    private:
        Key m_Key;
        KeyState m_KeyState;

    public:
        KeyEvent(Key key, KeyState state) : m_Key(key), m_KeyState(state) { m_IsNull = false; }

        Key GetKey() const { return m_Key; }

        KeyState GetKeyState() const { return m_KeyState; }

        // Override
        std::string GetName() const override
        {
            std::string name = "Key Event: ";
            name.append("Key: ").append(std::to_string(m_Key));
            name.append(" State: ");

            switch (m_KeyState)
            {
                case KeyState::Touched:
                    name.append("Touched");
                    break;
                case KeyState::Pressed:
                    name.append("Pressed");
                    break;
                case KeyState::Released:
                    name.append("Released");
                    break;
                case KeyState::Null:
                    break;
            }

            return name;
        }
    };
}