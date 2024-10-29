#include "Crayon.h"

using namespace Crayon::Core;
using namespace Crayon::Graphics;
using namespace Crayon::Events;

class Sandbox : public Application
{
private:
    // DATA

    std::vector<Vertex> vertices = {
        // Front face
        Vertex(glm::vec3(-1.0f, -1.0f, 1.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 0.0f)), // Bottom-left
        Vertex(glm::vec3(1.0f, -1.0f, 1.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 0.0f)),  // Bottom-right
        Vertex(glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 1.0f)),   // Top-right
        Vertex(glm::vec3(-1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 1.0f)),  // Top-left

        // Back face
        Vertex(glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec2(0.0f, 0.0f)), // Bottom-left
        Vertex(glm::vec3(1.0f, -1.0f, -1.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec2(1.0f, 0.0f)),  // Bottom-right
        Vertex(glm::vec3(1.0f, 1.0f, -1.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec2(1.0f, 1.0f)),   // Top-right
        Vertex(glm::vec3(-1.0f, 1.0f, -1.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec2(0.0f, 1.0f)),  // Top-left

        // Left face
        Vertex(glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f)), // Bottom-left
        Vertex(glm::vec3(-1.0f, 1.0f, -1.0f), glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec2(1.0f, 0.0f)),  // Top-left
        Vertex(glm::vec3(-1.0f, 1.0f, 1.0f), glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec2(1.0f, 1.0f)),   // Top-right
        Vertex(glm::vec3(-1.0f, -1.0f, 1.0f), glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec2(0.0f, 1.0f)),  // Bottom-right

        // Right face
        Vertex(glm::vec3(1.0f, -1.0f, -1.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f)), // Bottom-left
        Vertex(glm::vec3(1.0f, 1.0f, -1.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(1.0f, 0.0f)),  // Top-left
        Vertex(glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(1.0f, 1.0f)),   // Top-right
        Vertex(glm::vec3(1.0f, -1.0f, 1.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(0.0f, 1.0f)),  // Bottom-right

        // Top face
        Vertex(glm::vec3(-1.0f, 1.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f, 0.0f)), // Bottom-left
        Vertex(glm::vec3(1.0f, 1.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(1.0f, 0.0f)),  // Bottom-right
        Vertex(glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(1.0f, 1.0f)),   // Top-right
        Vertex(glm::vec3(-1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f, 1.0f)),  // Top-left

        // Bottom face
        Vertex(glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec2(0.0f, 0.0f)), // Bottom-left
        Vertex(glm::vec3(1.0f, -1.0f, -1.0f), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec2(1.0f, 0.0f)),  // Bottom-right
        Vertex(glm::vec3(1.0f, -1.0f, 1.0f), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec2(1.0f, 1.0f)),   // Top-right
        Vertex(glm::vec3(-1.0f, -1.0f, 1.0f), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec2(0.0f, 1.0f))   // Top-left
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

    // OBJECTS

    Camera camera; // Camera
    Light light;   // Light

    Mesh mesh; // GameObject
    Material material;
    glm::vec3 objectPosition;

    Shader shader; // Shader

public:
    Sandbox() : Application("Sandbox", 800, 600),
                camera(glm::vec3(4, 4, 3), glm::vec3(-25, 230, 0), *p_Window.get()),
                light(),
                mesh(vertices, indices, "assets/textures/test.png"),
                material(glm::vec3(0.8f, 0.3f, 0.2f)),
                objectPosition(glm::vec3(0, 0, -10.0f)),
                shader({
                    "assets/shaders/basic.vert",
                    "assets/shaders/basic.frag",
                })
    {
        GLCall(glEnable(GL_DEPTH_TEST));
        GLCall(glClearColor(0.2f, 0.4f, 0.6f, 1.0f));
    }

    void Update(double deltaTime) override
    {
        if (Input::GetKeyTouched(KeyCode::ESCAPE))
        {
            p_Window->ToggleCursor();
        }

        if (p_Window->IsCursorDisabled())
        {
            camera.Update(static_cast<float>(deltaTime));
        }
    }

    void Render() override
    {
        GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

        shader.Bind();

        // Object
        shader.SetUniformMatrix4f("u_Model", glm::translate(glm::mat4(1.0f), objectPosition));

        // Camera
        shader.SetUniformMatrix4f("u_View", camera.GetView());
        shader.SetUniformMatrix4f("u_Projection", camera.GetProjection());

        // Light
        shader.SetUniform3f("u_LightPosition", light.GetPosition());
        shader.SetUniform3f("u_LightColor", light.GetColor());

        // Material
        shader.SetUniform3f("u_BaseColor", material.GetColor());
        shader.SetUniform3f("u_Ambient", material.GetAmbient());
        shader.SetUniform3f("u_Diffuse", material.GetDiffuse());
        shader.SetUniform3f("u_Specular", material.GetSpecular());
        shader.SetUniform1f("u_Shininess", material.GetShininess());

        // Mesh
        mesh.GetVAO().Bind();
        mesh.GetIBO().Bind();
        mesh.GetTexture().Bind();

        // Render
        GLCall(glDrawElements(GL_TRIANGLES, mesh.GetIBO().GetCount(), GL_UNSIGNED_INT, nullptr));

        mesh.GetTexture().Unbind();
        mesh.GetIBO().Unbind();
        mesh.GetVAO().Unbind();

        shader.Unbind();
    }

    void RenderUI() override
    {
        // UI RENDERING
        ImGui::Begin("Controller");
        ImGui::Text("FPS: %.2f | DT: %.6f", m_FPS, m_DeltaTime);
        ImGui::Separator();
        ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f), "Object");
        ImGui::SliderFloat3("Obj Position", &objectPosition.x, -10.0f, 10.0f);
        ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f), "Camera");
        ImGui::Text("Cam Position: (%.2f, %.2f, %.2f)", camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z);
        ImGui::Text("Pitch: %.2f | Yaw: %.2f | Roll: %.2f)", camera.GetRotation().x, camera.GetRotation().y, camera.GetRotation().z);
        ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f), "Light");
        ImGui::SliderFloat3("Light Position", &light.Position().x, -100.0f, 100.0f);
        ImGui::SliderFloat3("Light Color", &light.Color().x, 0.0f, 1.0f);
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