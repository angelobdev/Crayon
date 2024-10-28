#pragma once

#include "crypch.h"
#include <glm/glm.hpp>

#include "Crayon/Core/Window.h"

#include "KeyEvent.h"
#include "MouseEvent.h"
#include "WindowEvent.h"

namespace Crayon::Events
{
    class Handler
    {
    private:
        static std::unordered_map<KeyCode, KeyState> s_KeyMap;
        static std::unordered_map<MouseButton, MouseState> s_MouseMap;
        static glm::vec2 s_CursorPos;

    public:
        static void Initialize(const Crayon::Core::Window &window);

        // GETTERS

        static KeyState GetKeyState(const KeyCode &key)
        {
            KeyState state = KeyState::Null;
            if (s_KeyMap.contains(key))
            {
                state = s_KeyMap[key];
                if (state == KeyState::Touched)
                    s_KeyMap[key] = KeyState::Pressed;
                if (state == KeyState::Released)
                    s_KeyMap.erase(key);
            }
            return state;
        }

        static MouseState GetMouseState(const MouseButton &button)
        {
            MouseState state = MouseState::Null;
            if (s_MouseMap.contains(button))
            {
                state = s_MouseMap[button];
                if (state == MouseState::Released)
                    s_MouseMap.erase(button);
            }
            return state;
        }

        static glm::vec2 GetCursorPosition()
        {
            return s_CursorPos;
        }
    };
}
