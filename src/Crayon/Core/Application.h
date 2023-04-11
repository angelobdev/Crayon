#pragma once

#include "Base.h"
#include "Window.h"

namespace Crayon
{
    class Application
    {
    private:
        std::shared_ptr<Window> m_Window;

    public:
        Application(const char *title, int width, int height);

        virtual ~Application();

        // Methods

        virtual void Update() = 0;

        virtual void Render() = 0;

        void Run();

        // Events

        virtual void OnWindowClosed() {}

        virtual void OnWindowResized(int width, int height) {}

        virtual void OnWindowMinimized() {}

        virtual void OnWindowGainFocus() {}

        virtual void OnWindowLostFocus() {}

    private:
        void OnEvent(Event *event);

        void HandleEvents();
    };

    Application *CreateApplication(); // To be defined in client
}