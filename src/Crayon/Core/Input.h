#pragma once

#include "crypch.h"
#include "Events.h"

namespace Crayon
{
    class Input
    {
    private:
        static std::unordered_map<Key, KeyState> s_KeyMap;
        static std::unordered_map<MouseButton, MouseButtonState> s_MouseMap;

    public:
        static KeyState GetKey(const Key &key);

        static void KeyCallback(const Key &key, const KeyState &keyState);

        static MouseButtonState GetMouseButton(const MouseButton &button);

        static void MouseButtonCallback(const MouseButton &button, const MouseButtonState &buttonState);
    };
}
