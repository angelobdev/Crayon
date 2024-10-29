#include "Window.h"

namespace Crayon::Core
{
    bool Window::s_GLFWInitialized = false;

    Window::Window(const char *title, int width, int height)
        : m_WindowedWidth(width), m_WindowedHeight(height),
          m_HasBeenClosed(false), m_IsFullscreen(false), m_IsCursorDisabled(false)
    {
        // Initializing GLFW
        if (!s_GLFWInitialized)
        {
            CRAYON_CORE_TRACE("Initializing GLFW...");
            if (!glfwInit())
            {
                CRAYON_CORE_FATAL("Failed to initialize the window!");
                exit(-1);
            }
        }

        // Setting window hints
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
        glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);

        // Creating window
        CRAYON_CORE_TRACE("Creating {} window ({}x{})...", title, width, height);
        p_Window = glfwCreateWindow(width, height, title, NULL, NULL);
        if (!p_Window)
        {
            CRAYON_CORE_FATAL("Failed to create the window!");
            glfwDestroyWindow(p_Window);
            glfwTerminate();
            exit(-1);
        }

        // Centering window
        int xPos, yPos;
        GetCenteredPosition(width, height, &xPos, &yPos);
        glfwSetWindowPos(p_Window, xPos, yPos);

        CRAYON_CORE_TRACE("Initializing Event System...");

        // Making context current
        glfwMakeContextCurrent(p_Window);

        // Initializing OpenGL
        CRAYON_CORE_TRACE("Initializing OpenGL...");
        if (!gladLoadGL())
        {
            CRAYON_CORE_FATAL("Failed to initialize OpenGL!");
            glfwDestroyWindow(p_Window);
            glfwTerminate();
            exit(-1);
        }
    }

    void Window::Close()
    {
        if (!this->m_HasBeenClosed)
        {
            glfwDestroyWindow(p_Window);
            glfwTerminate();
            this->m_HasBeenClosed = true;
        }
    }

    void Window::ToggleFullscreen()
    {
        // Inverting flag
        this->m_IsFullscreen = !this->m_IsFullscreen;

        if (this->m_IsFullscreen)
        {
            // Saving old size
            m_WindowedWidth = this->GetWidth();
            m_WindowedHeight = this->GetHeight();

            // Setting fullscreen mode
            GLFWmonitor *monitor = glfwGetPrimaryMonitor();
            const GLFWvidmode *vidMode = glfwGetVideoMode(monitor);
            glfwSetWindowMonitor(p_Window, monitor, 0, 0, vidMode->width, vidMode->height, vidMode->refreshRate);
        }
        else
        {
            // Setting windowed mode
            int xPos, yPos;
            GetCenteredPosition(m_WindowedWidth, m_WindowedHeight, &xPos, &yPos);
            glfwSetWindowMonitor(p_Window, NULL, xPos, yPos, m_WindowedWidth, m_WindowedHeight, GLFW_DONT_CARE);
        }
    }

    void Window::ToggleCursor()
    {
        this->m_IsCursorDisabled = !this->m_IsCursorDisabled;
        int glfwMode = this->m_IsCursorDisabled ? GLFW_CURSOR_DISABLED : GLFW_CURSOR_NORMAL;
        glfwSetInputMode(p_Window, GLFW_CURSOR, glfwMode);
    }

    void Window::GetCenteredPosition(int width, int height, int *xPos, int *yPos)
    {
        GLFWmonitor *monitor = glfwGetPrimaryMonitor();
        const GLFWvidmode *vidMode = glfwGetVideoMode(monitor);

        *xPos = vidMode->width / 2 - width / 2;
        *yPos = vidMode->height / 2 - height / 2;
    }
}