#include "Input.h"

namespace Crayon{

    std::unordered_map<Crayon::Key, Crayon::KeyState> Input::s_KeyMap = std::unordered_map<Crayon::Key, Crayon::KeyState>(104);
    std::unordered_map<MouseButton, MouseButtonState> Input::s_MouseMap = std::unordered_map<MouseButton, MouseButtonState>(4);

    Crayon::KeyState Input::GetKey(const Crayon::Key& key)
    {
        return s_KeyMap[key];
    }

    void Input::KeyCallback(const Crayon::Key& key, const Crayon::KeyState& keyState)
    {
        s_KeyMap.insert_or_assign(key, keyState);
    }

    MouseButtonState Input::GetMouseButton(const MouseButton &button)
    {
        return s_MouseMap[button];
    }

    void Input::MouseButtonCallback(const MouseButton &button, const MouseButtonState &buttonState)
    {
        s_MouseMap.insert_or_assign(button, buttonState);
    }
}