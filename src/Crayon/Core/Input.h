#pragma once

#include "crypch.h"

#include "Crayon/Events/Event.h"
#include "Crayon/Events/KeyEvent.h"
#include "Crayon/Events/MouseEvent.h"
#include "Crayon/Events/WindowEvent.h"

namespace Crayon
{
    class Input
    {
    private:
        static std::unordered_map<Key, KeyState> s_KeyMap;
        static std::unordered_map<MouseButton, MouseButtonState> s_MouseMap;
        static double s_MouseX, s_MouseY;

    public:

        // KEYBOARD FUNCTIONS

        static KeyState GetKey(const Key &key);

        static bool GetKeyDown(const Key &key);

        static void KeyCallback(const Key &key, const KeyState &keyState); // Callback

        // MOUSE FUNCTIONS

        static MouseButtonState GetMouseButton(const MouseButton &button);

        static void MouseButtonCallback(const MouseButton &button, const MouseButtonState &buttonState); // Callback

        // CURSOR FUNCTIONS

        static double GetMouseX();

        static double GetMouseY();

        static void MousePosCallback(double mouseX, double mouseY); // Callback
    };
}
