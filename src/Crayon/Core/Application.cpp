#include "Application.h"

namespace Crayon::Core
{
    // CONSTRUCTOR & DESTRUCTOR

    Application::Application(const char *title, int width, int height)
        : p_Window(std::make_shared<Window>(title, width, height))
    {
    }

    Application::~Application() = default;

    // METHODS

    void Application::Initialize()
    {
        CRAYON_CORE_TRACE("Initializing Event Handler...");
        Crayon::Events::Handler::Initialize(*p_Window.get());

        CRAYON_CORE_TRACE("Initializing ImGui Controller...");
        Crayon::Graphics::GUI::ImGuiController::Initialize(p_Window.get());

        CRAYON_CORE_INFO("Application has been initialized successfully!");
    }

    // RUN METHOD

    void Application::Run()
    {
        this->Initialize();

        double deltaTime = 0.01f;
        while (!p_Window->ShouldClose())
        {
            double start = glfwGetTime();

            // Handling Events
            p_Window->PollEvents();

            // Update
            this->Update(deltaTime);

            // Rendering
            this->Render();

            // UI (ImGui)
            Crayon::Graphics::GUI::ImGuiController::NewFrame();
            this->RenderUI();
            Crayon::Graphics::GUI::ImGuiController::Draw();

            p_Window->SwapBuffers();

            double end = glfwGetTime();
            deltaTime = end - start;
        }

        // Terminating ImGui
        Crayon::Graphics::GUI::ImGuiController::Terminate();

        p_Window->Close();
        CRAYON_CORE_INFO("Bye! <3");
    }
}