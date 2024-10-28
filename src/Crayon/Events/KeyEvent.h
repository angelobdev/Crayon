#pragma once

#include <GLFW/glfw3.h>

namespace Crayon::Events
{
    enum class KeyCode
    {
        // Numbers
        K0 = GLFW_KEY_0,
        K1 = GLFW_KEY_1,
        K2 = GLFW_KEY_2,
        K3 = GLFW_KEY_3,
        K4 = GLFW_KEY_4,
        K5 = GLFW_KEY_5,
        K6 = GLFW_KEY_6,
        K7 = GLFW_KEY_7,
        K8 = GLFW_KEY_8,
        K9 = GLFW_KEY_9,

        // Letters
        A = GLFW_KEY_A,
        B = GLFW_KEY_B,
        C = GLFW_KEY_C,
        D = GLFW_KEY_D,
        E = GLFW_KEY_E,
        F = GLFW_KEY_F,
        G = GLFW_KEY_G,
        H = GLFW_KEY_H,
        I = GLFW_KEY_I,
        J = GLFW_KEY_J,
        K = GLFW_KEY_K,
        L = GLFW_KEY_L,
        M = GLFW_KEY_M,
        N = GLFW_KEY_N,
        O = GLFW_KEY_O,
        P = GLFW_KEY_P,
        Q = GLFW_KEY_Q,
        R = GLFW_KEY_R,
        S = GLFW_KEY_S,
        T = GLFW_KEY_T,
        U = GLFW_KEY_U,
        V = GLFW_KEY_V,
        W = GLFW_KEY_W,
        X = GLFW_KEY_X,
        Y = GLFW_KEY_Y,
        Z = GLFW_KEY_Z,

        // Function keys
        F1 = GLFW_KEY_F1,
        F2 = GLFW_KEY_F2,
        F3 = GLFW_KEY_F3,
        F4 = GLFW_KEY_F4,
        F5 = GLFW_KEY_F5,
        F6 = GLFW_KEY_F6,
        F7 = GLFW_KEY_F7,
        F8 = GLFW_KEY_F8,
        F9 = GLFW_KEY_F9,
        F10 = GLFW_KEY_F10,
        F11 = GLFW_KEY_F11,
        F12 = GLFW_KEY_F12,

        // Special keys
        SPACE = GLFW_KEY_SPACE,
        ESCAPE = GLFW_KEY_ESCAPE,
        ENTER = GLFW_KEY_ENTER,
        TAB = GLFW_KEY_TAB,
        BACKSPACE = GLFW_KEY_BACKSPACE,
        INSERT = GLFW_KEY_INSERT,
        DELETE = GLFW_KEY_DELETE,
        LCTRL = GLFW_KEY_LEFT_CONTROL,
        LSHIFT = GLFW_KEY_LEFT_SHIFT,
        LALT = GLFW_KEY_LEFT_ALT,
        LSUPER = GLFW_KEY_LEFT_SUPER,
        RCTRL = GLFW_KEY_RIGHT_CONTROL,
        RSHIFT = GLFW_KEY_RIGHT_SHIFT,
        RALT = GLFW_KEY_RIGHT_ALT,
        RSUPER = GLFW_KEY_RIGHT_SUPER,

        // Arrows
        RIGHT = GLFW_KEY_RIGHT,
        LEFT = GLFW_KEY_LEFT,
        DOWN = GLFW_KEY_DOWN,
        UP = GLFW_KEY_UP,

        // Other keys
        PAGE_UP = GLFW_KEY_PAGE_UP,
        PAGE_DOWN = GLFW_KEY_PAGE_DOWN,
        HOME = GLFW_KEY_HOME,
        END = GLFW_KEY_END,
        CAPS_LOCK = GLFW_KEY_CAPS_LOCK,
        SCROLL_LOCK = GLFW_KEY_SCROLL_LOCK,
        NUM_LOCK = GLFW_KEY_NUM_LOCK,
        PRINT_SCREEN = GLFW_KEY_PRINT_SCREEN,
        PAUSE = GLFW_KEY_PAUSE,
        KP_0 = GLFW_KEY_KP_0,
        KP_1 = GLFW_KEY_KP_1,
        KP_2 = GLFW_KEY_KP_2,
        KP_3 = GLFW_KEY_KP_3,
        KP_4 = GLFW_KEY_KP_4,
        KP_5 = GLFW_KEY_KP_5,
        KP_6 = GLFW_KEY_KP_6,
        KP_7 = GLFW_KEY_KP_7,
        KP_8 = GLFW_KEY_KP_8,
        KP_9 = GLFW_KEY_KP_9,
        KP_DECIMAL = GLFW_KEY_KP_DECIMAL,
        KP_DIVIDE = GLFW_KEY_KP_DIVIDE,
        KP_MULTIPLY = GLFW_KEY_KP_MULTIPLY,
        KP_SUBTRACT = GLFW_KEY_KP_SUBTRACT,
        KP_ADD = GLFW_KEY_KP_ADD,
        KP_ENTER = GLFW_KEY_KP_ENTER,
        KP_EQUAL = GLFW_KEY_KP_EQUAL,
        LEFT_BRACKET = GLFW_KEY_LEFT_BRACKET,
        RIGHT_BRACKET = GLFW_KEY_RIGHT_BRACKET,
        SEMICOLON = GLFW_KEY_SEMICOLON,
        APOSTROPHE = GLFW_KEY_APOSTROPHE,
        COMMA = GLFW_KEY_COMMA,
        PERIOD = GLFW_KEY_PERIOD,
        SLASH = GLFW_KEY_SLASH,
        BACKSLASH = GLFW_KEY_BACKSLASH,
        GRAVE_ACCENT = GLFW_KEY_GRAVE_ACCENT,
        WORLD_1 = GLFW_KEY_WORLD_1,
        WORLD_2 = GLFW_KEY_WORLD_2
    };

    enum class KeyState
    {
        Null,
        Touched,
        Pressed,
        Released,
    };

    struct KeyEvent
    {
    private:
        const KeyCode m_KeyCode;
        const KeyState m_KeyState;

    public:
        KeyEvent(KeyCode keyCode, KeyState keyState)
            : m_KeyCode(keyCode), m_KeyState(keyState)
        {
        }

        const KeyCode GetKeyCode() const
        {
            return m_KeyCode;
        }

        const KeyState GetKeyState() const
        {
            return m_KeyState;
        }
    };
}