#include "crypch.h"
#include "Application.h"

namespace Crayon {
    Application::Application(const char *title, int width, int height)
            : m_Window(std::make_shared<Window>(title, width, height)) {

    }

    Application::~Application() = default;

    void Application::OnEvent(Event *event) {
        // ----- HANDLING CALLBACKS -----
        // CRAYON_CORE_WARN("Retrieved event: {}", event->GetName());

        // Keyboard
        if (auto *keyEvent = dynamic_cast<KeyEvent *>(event)) {
            switch (keyEvent->GetKeyState()) {
                case KeyState::Touched:
                    this->OnKeyTouched(keyEvent->GetKey());
                    break;
                case KeyState::Pressed:
                    this->OnKeyPressed(keyEvent->GetKey());
                    break;
                case KeyState::Released:
                    this->OnKeyReleased(keyEvent->GetKey());
                    break;
                case NoKState:
                    break;
            }
        }

        // Mouse Button
        if (auto *mbEvent = dynamic_cast<MouseButtonEvent *>(event)) {
            switch (mbEvent->GetButtonState()) {
                case MouseButtonState::Clicked:
                    this->OnMouseButtonClicked(mbEvent->GetButton());
                    break;
                case MouseButtonState::Unclicked:
                    this->OnMouseButtonReleased(mbEvent->GetButton());
                    break;
                case NoBState:
                    break;
            }
        }

        // Mouse Movement
        if (auto *mmEvent = dynamic_cast<MouseMovedEvent *>(event)) {
            this->OnMouseMoved(mmEvent->GetX(), mmEvent->GetY());
        }

        // Window Events
        if (auto *wdEvent = dynamic_cast<WindowEvent *>(event)) {
            switch (wdEvent->GetWindowState()) {
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

    void Application::HandleEvents() {
        Event *lastEvent = EventDispatcher::Retrieve();
        if (lastEvent != nullptr) { OnEvent(lastEvent); }
        delete lastEvent;
    }

    void Application::Run() {
        glClearColor(0.2f, 0.4f, 0.6f, 1.0f);

        while (!m_Window->ShouldClose()) {
            // Handling Events
            this->HandleEvents();

            // Update

            // Render
            glClear(GL_COLOR_BUFFER_BIT);

            // Window stuff
            m_Window->PollEvents();
            m_Window->SwapBuffers();
        }

        // Dispatching remaining events
        while (EventDispatcher::GetQueueSize() > 0)
            this->HandleEvents();

        m_Window->Close();
    }
}