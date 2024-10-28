#include "Crayon.h"

using namespace Crayon::Core;
using namespace Crayon::Graphics;
using namespace Crayon::Events;

class Sandbox : public Application
{
private:
    std::vector<float> vertices = {
        // POSITION         // COLOR         // TEXTURE COORD
        -0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, // v1
        +0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, // v2
        -0.5f, +0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, // v3
        +0.5f, +0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, // v4
    };

    std::vector<unsigned int> indices = {
        0, 1, 2, // t1
        1, 3, 2, // t2
    };

    std::unique_ptr<Core::VertexArray> vertexArray;
    std::unique_ptr<Core::VertexBuffer<float>> vertexBuffer;
    std::unique_ptr<Core::IndexBuffer> indexBuffer;
    std::unique_ptr<Core::Shader> shader;
    std::unique_ptr<Core::Texture> texture;

    glm::vec3 objectPosition = glm::vec3(0.0f, 0.0f, -2.0f);
    std::unique_ptr<Camera> camera;

public:
    Sandbox() : Application("Sandbox", 800, 600)
    {
        GLCall(glClearColor(0.2f, 0.4f, 0.6f, 1.0f));

        vertexArray = std::make_unique<Core::VertexArray>();
        vertexArray->Bind();

        vertexBuffer = std::make_unique<Core::VertexBuffer<float>>(vertices, std::vector<Core::VertexLayout>({{3, GL_FLOAT},
                                                                                                              {3, GL_FLOAT},
                                                                                                              {2, GL_FLOAT}}));
        indexBuffer = std::make_unique<Core::IndexBuffer>(indices);
        shader = std::make_unique<Core::Shader>("assets/shaders/basic.glsl", true);
        texture = std::make_unique<Core::Texture>("assets/textures/test.png");

        camera = std::make_unique<Camera>(glm::vec3(0, 0, 0));
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

        shader->SetUniformMatrix4f("u_Projection",
                                   glm::perspective(
                                       glm::radians(70.0f),
                                       p_Window->GetAspectRatio(),
                                       0.0f,
                                       100.0f));

        texture->Bind(1);
        shader->SetUniform1i("u_Texture", 1);

        vertexArray->Bind();
        indexBuffer->Bind();

        GLCall(glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, nullptr));

        indexBuffer->Unbind();
        vertexArray->Unbind();

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