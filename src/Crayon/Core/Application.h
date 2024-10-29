#pragma once

#include "Base.h"
#include "Crayon/Events/Event.h"
#include "Crayon/Graphics/GUI/ImGuiController.h"
#include "Window.h"

namespace Crayon::Core
{
    class Application
    {

    protected:
        std::shared_ptr<Window> p_Window;
        double m_DeltaTime, m_FPS;

    public:
        Application(const char *title, int width, int height);

        virtual ~Application();

        // Methods to implement in client

        virtual void Update(double deltaTime) = 0;

        virtual void Render() = 0;

        virtual void RenderUI() {}

        void Run();

        // Events

        virtual void OnWindowClosed() {}

        virtual void OnWindowResized(int width, int height)
        {
            glfwSetWindowSize(p_Window->GetPointer(), width, height);
            glViewport(0, 0, width, height);
            this->Render();
        }

        virtual void OnWindowMinimized() {}

        virtual void OnWindowGainFocus() {}

        virtual void OnWindowLostFocus() {}

    private:
        void Initialize();
    };

}

Crayon::Core::Application *CreateApplication(); // To be defined in client