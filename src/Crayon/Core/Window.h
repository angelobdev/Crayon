#pragma once

#include <glad/glad.h>

#include <GLFW/glfw3.h>

#include "Logger.h"

#include "Crayon/Events/Event.h"
#include "Crayon/Events/KeyEvent.h"
#include "Crayon/Events/MouseEvent.h"
#include "Crayon/Events/WindowEvent.h"

namespace Crayon
{
    class Window
    {
    private:
        static bool s_GLFWInitialized;

        GLFWwindow *p_Window;
        bool m_HasBeenClosed;
        int m_WindowedWidth, m_WindowedHeight;
        bool m_IsFullscreen;

    public:
        Window(const char *title, int width, int height);
        Window(const Window &window) = delete;
        Window() = delete;

        ~Window() { this->Close(); }

        // METHODS

        static void PollEvents() { glfwPollEvents(); }

        void SwapBuffers() { glfwSwapBuffers(p_Window); }

        void Close();

        void ToggleFullscreen();

        // GETTERS AND SETTERS

        bool ShouldClose() const { return glfwWindowShouldClose(p_Window); }

        int GetWidth() const
        {
            int width;
            glfwGetWindowSize(p_Window, &width, NULL);
            return width;
        }

        int GetHeight() const
        {
            int height;
            glfwGetWindowSize(p_Window, NULL, &height);
            return height;
        }

        GLFWwindow *GetPointer() { return p_Window; }

        float GetAspectRatio()
        {
            float ww = (float)GetWidth();
            float hh = (float)GetHeight();
            float ar = ww / hh;
            //            CRAYON_CORE_TRACE("WINDOW: ({}, {}) = {}", ww, hh, ar);
            return ar;
        }

    private:
        static void GetCenteredPosition(int width, int height, int *xPos, int *yPos);
    };
}