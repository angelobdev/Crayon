#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Logger.h"
#include "Events.h"

namespace Crayon
{
    class Window
    {
    private:
        GLFWwindow *m_Window;

        bool m_HasBeenClosed;

        int m_WindowedWidth, m_WindowedHeight;
        bool m_IsFullscreen;

    public:
        Window(const char *title, int width, int height);

        ~Window()
        { this->Close(); }

        // METHODS

        static void PollEvents()
        { glfwPollEvents(); }

        void SwapBuffers()
        { glfwSwapBuffers(m_Window); }

        void Close();

        void ToggleFullscreen();

        // GETTERS AND SETTERS

        [[nodiscard]] bool ShouldClose() const
        { return glfwWindowShouldClose(m_Window); }

        [[nodiscard]] int GetWidth() const
        {
            int width;
            glfwGetWindowSize(m_Window, &width, NULL);
            return width;
        }

        [[nodiscard]] int GetHeight() const
        {
            int height;
            glfwGetWindowSize(m_Window, NULL, &height);
            return height;
        }

    private:
        static void GetCenteredPosition(int width, int height, int *xpos, int *ypos);

    };
}