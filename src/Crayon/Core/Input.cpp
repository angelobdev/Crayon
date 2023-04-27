#include "Input.h"
#include "Logger.h"

namespace Crayon
{
    // INITIALIZATIONS

    std::unordered_map<Key, KeyState> Input::s_KeyMap
            = std::unordered_map<Key, KeyState>(104);

    std::unordered_map<MouseButton, MouseButtonState> Input::s_MouseMap
            = std::unordered_map<MouseButton, MouseButtonState>(4);

    double Input::s_MouseX = 0.0f, Input::s_MouseY = 0.0f;

    // KEYBOARD FUNCTIONS

    KeyState Input::GetKey(const Key &key)
    {
        return s_KeyMap[key];
    }

    bool Input::GetKeyDown(const Key &key)
    {
        KeyState state = GetKey(key);
        return (state == KeyState::Touched || state == KeyState::Pressed);
    }

    void Input::KeyCallback(const Key &key, const KeyState &keyState)
    {
        s_KeyMap.insert_or_assign(key, keyState);
    }

    // MOUSE FUNCTIONS

    MouseButtonState Input::GetMouseButton(const MouseButton &button)
    {
        return s_MouseMap[button];
    }

    void Input::MouseButtonCallback(const MouseButton &button, const MouseButtonState &buttonState)
    {
        s_MouseMap.insert_or_assign(button, buttonState);
    }

    // CURSOR FUNCTIONS

    double Input::GetMouseX()
    { return s_MouseX; }

    double Input::GetMouseY()
    { return s_MouseY; }

    void Input::MousePosCallback(double mouseX, double mouseY)
    {
        s_MouseX = mouseX;
        s_MouseY = mouseY;
    }

}