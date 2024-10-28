#pragma once

#include "crypch.h"
#include <glm/glm.hpp>

#include "Crayon/Events/Event.h"
#include "Crayon/Events/KeyEvent.h"
#include "Crayon/Events/MouseEvent.h"
#include "Crayon/Events/WindowEvent.h"

namespace Crayon
{
    class Input
    {
    public:
        static void Initialize(const Window &window)
        {
            Events::Handler::Initialize(window);
        }

        // KEYBOARD FUNCTIONS

        static const bool GetKeyTouched(const Events::KeyCode &key)
        {
            return Events::Handler::GetKeyState(key) == Events::KeyState::Touched;
        }

        static const bool GetKeyPressed(const Events::KeyCode &key)
        {
            return Events::Handler::GetKeyState(key) == Events::KeyState::Pressed;
        }

        static const bool GetKeyReleased(const Events::KeyCode &key)
        {
            return Events::Handler::GetKeyState(key) == Events::KeyState::Released;
        }

        static const bool GetKeyDown(const Events::KeyCode &key)
        {
            return GetKeyTouched(key) || GetKeyPressed(key);
        }

        // MOUSE FUNCTIONS

        static const bool GetMouseTouched(const Events::MouseButton &key)
        {
            return Events::Handler::GetMouseState(key) == Events::MouseState::Clicked;
        }

        static const bool GetMouseReleased(const Events::MouseButton &key)
        {
            return Events::Handler::GetMouseState(key) == Events::MouseState::Released;
        }

        // CURSOR FUNCTIONS

        static const glm::vec2 GetCursorPosition()
        {
            return Events::Handler::GetCursorPosition();
        }

        static const double GetMouseX()
        {
            return GetCursorPosition().x;
        }

        static const double GetMouseY()
        {
            return GetCursorPosition().y;
        }
    };
}
