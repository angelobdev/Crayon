#pragma once

#include "Event.h"

namespace Crayon
{
    using Key = int;
    enum class KeyState
    {
        Null, Touched, Pressed, Released
    };

    static const char *GetKeyStateName(const KeyState &state)
    {
        char *name = (char *) malloc(sizeof(char) * 24);
        switch (state)
        {
            case KeyState::Null:
                sprintf(name, "Null");
                break;
            case KeyState::Touched:
                sprintf(name, "Touched");
                break;
            case KeyState::Pressed:
                sprintf(name, "Pressed");
                break;
            case KeyState::Released:
                sprintf(name, "Released");
                break;
        }
        return name;
    }

    class KeyEvent : public Event
    {
    private:
        Key m_Key;
        KeyState m_KeyState;

    public:
        KeyEvent(Key key, KeyState state) : m_Key(key), m_KeyState(state)
        { m_IsNull = false; }

        Key GetKey() const
        { return m_Key; }

        KeyState GetKeyState() const
        { return m_KeyState; }

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