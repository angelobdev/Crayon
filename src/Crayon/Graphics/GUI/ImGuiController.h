#pragma once

#include "Crayon/Core/Window.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

namespace Crayon::Graphics::GUI
{
    class ImGuiController
    {
    private:
        static Crayon::Core::Window *s_Window;
        static ImGuiIO s_IO;

    public:
        static void Initialize(Crayon::Core::Window *window);

        static void NewFrame();

        static void Draw();

        static void Terminate();

        static ImGuiIO &GetIO() { return s_IO; }
    };
}
