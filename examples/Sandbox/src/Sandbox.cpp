#include "Crayon.h"

using namespace Crayon::Core;
using namespace Crayon::Graphics;
using namespace Crayon::Events;

class Sandbox : public Application
{
private:
    // DATA

    std::vector<float> vertices = {
        // Front face
        -1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f, // Bottom-left,  normal (0, 0, 1)
        1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f,  // Bottom-right, normal (0, 0, 1)
        1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f,   // Top-right,    normal (0, 0, 1)
        -1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f,  // Top-left,     normal (0, 0, 1)

        // Back face
        -1.0f, -1.0f, -1.0f, 0.0f, 0.0f, -1.0f, // Bottom-left,  normal (0, 0, -1)
        1.0f, -1.0f, -1.0f, 0.0f, 0.0f, -1.0f,  // Bottom-right, normal (0, 0, -1)
        1.0f, 1.0f, -1.0f, 0.0f, 0.0f, -1.0f,   // Top-right,    normal (0, 0, -1)
        -1.0f, 1.0f, -1.0f, 0.0f, 0.0f, -1.0f,  // Top-left,     normal (0, 0, -1)

        // Left face
        -1.0f, -1.0f, -1.0f, -1.0f, 0.0f, 0.0f, // Bottom-left,  normal (-1, 0, 0)
        -1.0f, 1.0f, -1.0f, -1.0f, 0.0f, 0.0f,  // Top-left,     normal (-1, 0, 0)
        -1.0f, 1.0f, 1.0f, -1.0f, 0.0f, 0.0f,   // Top-right,    normal (-1, 0, 0)
        -1.0f, -1.0f, 1.0f, -1.0f, 0.0f, 0.0f,  // Bottom-right, normal (-1, 0, 0)

        // Right face
        1.0f, -1.0f, -1.0f, 1.0f, 0.0f, 0.0f, // Bottom-left,  normal (1, 0, 0)
        1.0f, 1.0f, -1.0f, 1.0f, 0.0f, 0.0f,  // Top-left,     normal (1, 0, 0)
        1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,   // Top-right,    normal (1, 0, 0)
        1.0f, -1.0f, 1.0f, 1.0f, 0.0f, 0.0f,  // Bottom-right, normal (1, 0, 0)

        // Top face
        -1.0f, 1.0f, -1.0f, 0.0f, 1.0f, 0.0f, // Bottom-left,  normal (0, 1, 0)
        1.0f, 1.0f, -1.0f, 0.0f, 1.0f, 0.0f,  // Bottom-right, normal (0, 1, 0)
        1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f,   // Top-right,    normal (0, 1, 0)
        -1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f,  // Top-left,     normal (0, 1, 0)

        // Bottom face
        -1.0f, -1.0f, -1.0f, 0.0f, -1.0f, 0.0f, // Bottom-left,  normal (0, -1, 0)
        1.0f, -1.0f, -1.0f, 0.0f, -1.0f, 0.0f,  // Bottom-right, normal (0, -1, 0)
        1.0f, -1.0f, 1.0f, 0.0f, -1.0f, 0.0f,   // Top-right,    normal (0, -1, 0)
        -1.0f, -1.0f, 1.0f, 0.0f, -1.0f, 0.0f   // Top-left,     normal (0, -1, 0)
    };

    std::vector<unsigned int> indices = {
        // Front face
        0, 1, 2, 2, 3, 0,
        // Back face
        4, 5, 6, 6, 7, 4,
        // Left face
        8, 9, 10, 10, 11, 8,
        // Right face
        12, 13, 14, 14, 15, 12,
        // Top face
        16, 17, 18, 18, 19, 16,
        // Bottom face
        20, 21, 22, 22, 23, 20};

    std::vector<Core::VertexLayout> layout = {
        {3, GL_FLOAT}, // position
        {3, GL_FLOAT}  // normal
    };

    // OBJECTS

    std::unique_ptr<Camera> camera; // Camera

    std::unique_ptr<Mesh<float>> mesh; // GameObject
    glm::vec3 objectPosition = glm::vec3(0.0f, 0.0f, -10.0f);

    std::unique_ptr<Core::Shader> shader; // Shader
    std::unique_ptr<Light> light;         // Light
    std::unique_ptr<Material> material;   // Material

public:
    Sandbox() : Application("Sandbox", 800, 600)
    {
        GLCall(glEnable(GL_DEPTH_TEST));
        GLCall(glClearColor(0.2f, 0.4f, 0.6f, 1.0f));

        camera = std::make_unique<Camera>(glm::vec3(4, 4, 3), glm::vec3(-25, 230, 0), *p_Window.get());
        mesh = std::make_unique<Mesh<float>>(vertices, layout, indices);
        shader = std::make_unique<Core::Shader>("assets/shaders/basic.glsl", true);
        light = std::make_unique<Light>();
        material = std::make_unique<Material>(glm::vec3(0.8f, 0.3f, 0.2f));
    }

    void Update(double deltaTime) override
    {
        if (Input::GetKeyTouched(KeyCode::ESCAPE))
        {
            p_Window->ToggleCursor();
        }

        if (p_Window->IsCursorDisabled())
        {
            camera->Update(static_cast<float>(deltaTime));
        }
    }

    void Render() override
    {
        GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

        shader->Bind();

        shader->SetUniformMatrix4f("u_Model", glm::translate(glm::mat4(1.0f), objectPosition));
        shader->SetUniformMatrix4f("u_View", camera->GetView());
        shader->SetUniformMatrix4f("u_Projection", camera->GetProjection());

        shader->SetUniform3f("u_LightPosition", light->GetPosition());
        shader->SetUniform3f("u_LightColor", light->GetColor());

        shader->SetUniform3f("u_BaseColor", material->GetColor());
        shader->SetUniform1f("u_Ambient", material->GetAmbient());
        shader->SetUniform1f("u_Diffuse", material->GetDiffuse());
        shader->SetUniform1f("u_Specular", material->GetSpecular());

        mesh->GetVAO().Bind();
        mesh->GetIBO().Bind();

        GLCall(glDrawElements(GL_TRIANGLES, mesh->GetIBO().GetCount(), GL_UNSIGNED_INT, nullptr));

        mesh->GetIBO().Unbind();
        mesh->GetVAO().Unbind();

        shader->Unbind();
    }

    void RenderUI() override
    {
        // UI RENDERING
        ImGui::Begin("Controller");
        ImGui::SliderFloat3("Object Position", &objectPosition.x, -10.0f, 10.0f);
        ImGui::Text("Camera Position: (%.2f, %.2f, %.2f)", camera->GetPosition().x, camera->GetPosition().y, camera->GetPosition().z);
        ImGui::Text("Pitch: %.2f | Yaw: %.2f | Roll: %.2f)", camera->GetRotation().x, camera->GetRotation().y, camera->GetRotation().z);
        ImGui::Text("Camera Up: (%.2f, %.2f, %.2f)", camera->GetUp().x, camera->GetUp().y, camera->GetUp().z);
        ImGui::Text("Camera Front: (%.2f, %.2f, %.2f)", camera->GetFront().x, camera->GetFront().y, camera->GetFront().z);
        ImGui::Text("Camera Right: (%.2f, %.2f, %.2f)", camera->GetRight().x, camera->GetRight().y, camera->GetRight().z);
        ImGui::End();
    }

    ~Sandbox() override
    {
    }
};

Application *CreateApplication()
{
    return new Sandbox();
}