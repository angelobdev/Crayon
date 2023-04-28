#include "crypch.h"
#include "Application.h"
#include "Input.h"

namespace Crayon
{
    // CONSTRUCTOR & DESTRUCTOR

    Application::Application(const char *title, int width, int height)
            : m_Window(std::make_shared<Window>(title, width, height))
    {

    }

    Application::~Application() = default;

    // METHODS

    void Application::Initialize()
    {
        CRAYON_CORE_INFO("Welcome to Crayon Engine!");
        Crayon::ImGuiController::Initialize(m_Window.get());
    }

    void Application::HandleEvents()
    {
        Event *lastEvent = EventDispatcher::Retrieve();
        if (lastEvent != nullptr) { OnEvent(lastEvent); }
        delete lastEvent;
    }

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

    // RUN METHODS

    void Application::Run()
    {
        this->Initialize();

        double deltaTime = 0.01f;
        while (!m_Window->ShouldClose())
        {
            double start = glfwGetTime();

            // Handling Events
            m_Window->PollEvents();
            this->HandleEvents();

            // Update
            this->Update(deltaTime);

            // Rendering
            this->Render();

            // UI (ImGui)
            Crayon::ImGuiController::NewFrame();
            this->RenderUI();
            Crayon::ImGuiController::Draw();

            m_Window->SwapBuffers();

            double end = glfwGetTime();
            deltaTime = end - start;
        }

        // Terminating ImGui
        ImGuiController::Terminate();

        // Dispatching remaining events (Not sure if this is needed anymore)
        while (EventDispatcher::GetQueueSize() > 0)
            this->HandleEvents();

        m_Window->Close();
        CRAYON_CORE_INFO("Bye! <3");
    }
}