#include "Event.h"

namespace Crayon::Events
{
    std::unordered_map<KeyCode, KeyState> Handler::s_KeyMap = std::unordered_map<KeyCode, KeyState>();
    std::unordered_map<MouseButton, MouseState> Handler::s_MouseMap = std::unordered_map<MouseButton, MouseState>();
    glm::vec2 Handler::s_CursorPos(0, 0);

    void Handler::Initialize(const Crayon::Core::Window &window)
    {
        // Key Callbacks
        glfwSetKeyCallback(
            window.GetPointer(),
            [](GLFWwindow *window, int key, int scancode, int action, int mods)
            {
                auto keyCode = static_cast<KeyCode>(key);

                switch (action)
                {
                case GLFW_PRESS:
                    s_KeyMap[keyCode] = KeyState::Touched;
                    break;
                case GLFW_REPEAT:
                    s_KeyMap[keyCode] = KeyState::Pressed;
                    break;
                case GLFW_RELEASE:
                    s_KeyMap[keyCode] = KeyState::Released;
                    break;
                default:
                    CRAYON_CORE_FATAL("Received invalid Key Action from GLFW: {}", action);
                    break;
                }
            });

        // Mouse Movement Callbacks
        glfwSetCursorPosCallback(
            window.GetPointer(),
            [](GLFWwindow *window, double cursorX, double cursorY)
            {
                s_CursorPos = glm::vec2(cursorX, cursorY);
            });

        // Mouse Button Callbacks
        glfwSetMouseButtonCallback(
            window.GetPointer(),
            [](GLFWwindow *window, int button, int action, int mods)
            {
                auto mouseButton = static_cast<MouseButton>(button);

                switch (action)
                {
                case GLFW_PRESS:
                    s_MouseMap[mouseButton] = MouseState::Clicked;
                    break;
                case GLFW_RELEASE:
                    s_MouseMap[mouseButton] = MouseState::Released;
                    break;
                default:
                    CRAYON_CORE_FATAL("Received invalid Mouse Action from GLFW: {}", action);
                    break;
                }
            });

        // Window Closed Callback
        glfwSetWindowCloseCallback(
            window.GetPointer(),
            [](GLFWwindow *window)
            {
                // TODO:
            });

        // Window Resized
        glfwSetWindowSizeCallback(
            window.GetPointer(),
            [](GLFWwindow *window, int width, int height)
            {
                // TODO:
            });

        glfwSetFramebufferSizeCallback(
            window.GetPointer(),
            [](GLFWwindow *window, int width, int height)
            {
                // TODO:
            });

        // Window Minimized
        glfwSetWindowIconifyCallback(
            window.GetPointer(),
            [](GLFWwindow *window, int minimized)
            {
                // TODO:
            });

        // Window Focused, Unfocused
        glfwSetWindowFocusCallback(
            window.GetPointer(),
            [](GLFWwindow *window, int focused)
            {
                // TODO:
            });
    }

}
