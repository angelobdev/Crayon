#pragma once

#include "Crayon/Core/Window.h"

#include "imgui.h"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_glfw.h"

namespace Crayon
{
    class ImGuiController
    {
    private:
        static Crayon::Window *s_Window;
        static ImGuiIO s_IO;

    public:
        static void Initialize(Crayon::Window *window);

        static void NewFrame();

        static void Draw();

        static void Terminate();

        static ImGuiIO &GetIO() { return s_IO; }

    };
}
