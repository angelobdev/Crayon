#include "Crayon.h"

class Sandbox : public Crayon::Application
{
public:
    Sandbox() : Application("Sandbox", 800, 600)
    {
        glClearColor(0.2f, 0.4f, 0.6f, 1.0f);
    }

    ~Sandbox() override
    {

    }

    void Update() override
    {

    }

    void Render() override
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        Crayon::ImGuiController::NewFrame();

        ImGui::ShowDemoWindow();

        ImGui::ShowAboutWindow();

        ImGui::Begin("Custom window");
        if(ImGui::Button("Ciao")) CRAYON_TRACE("Clicked button");
        ImGui::End();

        Crayon::ImGuiController::Draw();

    }

};

Crayon::Application *Crayon::CreateApplication()
{
    return new Sandbox();
}