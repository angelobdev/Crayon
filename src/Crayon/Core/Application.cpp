#include "crypch.h"
#include "Application.h"
#include "Input.h"

namespace Crayon
{
    Application::Application(const char *title, int width, int height)
            : m_Window(std::make_shared<Window>(title, width, height))
    {
        Crayon::ImGuiController::Initialize(m_Window.get());
    }

    Application::~Application() = default;

    void Application::OnEvent(Event *event)
    {
        // ----- HANDLING CALLBACKS -----

        // Keyboard
        if (auto *keyEvent = dynamic_cast<KeyEvent *>(event))
        {
            Input::KeyCallback(keyEvent->GetKey(), keyEvent->GetKeyState());
        }

        // Mouse Button
        if (auto *mbEvent = dynamic_cast<MouseButtonEvent *>(event))
        {
            Input::MouseButtonCallback(mbEvent->GetButton(), mbEvent->GetButtonState());
        }

        // Mouse Movement
        if (auto *mmEvent = dynamic_cast<MouseMovedEvent *>(event))
        {
            Input::MousePosCallback(mmEvent->GetX(), mmEvent->GetY());
        }

        // Window Events
        if (auto *wdEvent = dynamic_cast<WindowEvent *>(event))
        {
            switch (wdEvent->GetWindowState())
            {
                case WindowState::Closed:
                    this->OnWindowClosed();
                    break;

                case WindowState::Resized:
                    this->OnWindowResized(m_Window->GetWidth(), m_Window->GetHeight());
                    break;

                case WindowState::Minimized:
                    this->OnWindowMinimized();
                    break;

                case WindowState::Focused:
                    this->OnWindowGainFocus();
                    break;

                case WindowState::Unfocused:
                    this->OnWindowLostFocus();
                    break;
            }
        }

    }

    void Application::HandleEvents()
    {
        Event *lastEvent = EventDispatcher::Retrieve();
        if (lastEvent != nullptr) { OnEvent(lastEvent); }
        delete lastEvent;
    }

    void Application::Run()
    {
        while (!m_Window->ShouldClose())
        {
            // Handling Events
            m_Window->PollEvents();
            this->HandleEvents();

            // Update
            this->Update();

            // Render
            this->Render();
            m_Window->SwapBuffers();
        }

        // Terminating ImGui
        ImGuiController::Terminate();

        // Dispatching remaining events
        while (EventDispatcher::GetQueueSize() > 0)
            this->HandleEvents();

        m_Window->Close();
    }
}