#include "Crayon.h"

#include "Crayon/Graphics/VertexArray.h"
#include "Crayon/Graphics/VertexBuffer.h"
#include "Crayon/Graphics/IndexBuffer.h"
#include "Crayon/Graphics/Shader.h"

#include "Crayon/Utilities/ResourceLoader.h"

class Sandbox : public Crayon::Application
{
private:
    std::vector<float> vertices = {
            -0.5f, -0.5f, 0.0f,
            +0.5f, -0.5f, 0.0f,
            -0.5f, +0.5f, 0.0f,
            +0.5f, +0.5f, 0.0f,
    };

    std::vector<unsigned int> indices = {
            0, 1, 2,
            1, 3, 2
    };

    Crayon::VertexArray vertexArray = Crayon::VertexArray();
    Crayon::VertexBuffer vertexBuffer = Crayon::VertexBuffer(vertices, {{3, GL_FLOAT}});
    Crayon::IndexBuffer indexBuffer = Crayon::IndexBuffer(indices);
    Crayon::Shader shader = Crayon::Shader(Crayon::ResourceLoader::LoadFileAsString("assets/shaders/basic.glsl", true));

public:
    Sandbox() : Application("Sandbox", 800, 600)
    {
        GLCall(glClearColor(0.2f, 0.4f, 0.6f, 1.0f));
        vertexArray.LinkBuffer(vertexBuffer);
    }

    ~Sandbox() override
    {

    }

    void Update() override
    {

    }

    void Render() override
    {
        // CUSTOM RENDERING
        GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

        vertexArray.Bind();
        indexBuffer.Bind();
        shader.Bind();

        GLCall(glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, nullptr));
    }

    void RenderUI() override
    {
        // UI RENDERING
//        ImGui::ShowDemoWindow();
//
//        ImGui::ShowAboutWindow();
//
//        ImGui::Begin("Custom window");
//        if (ImGui::Button("Ciao")) CRAYON_TRACE("Clicked button");
//        ImGui::End();
    }

};

Crayon::Application *Crayon::CreateApplication()
{
    return new Sandbox();
}