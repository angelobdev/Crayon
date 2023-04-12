#include "Crayon.h"

#include "Crayon/Graphics/Shader.h"
#include "Crayon/Utilities/ResourceLoader.h"

class Sandbox : public Crayon::Application
{
private:

    unsigned int vao, vbo, ibo;

    std::string sourceCode;
    Crayon::Shader shader;

    std::vector<float> vertices = {
            -0.5f, +0.5f, 0.0f,
            +0.5f, +0.5f, 0.0f,
            -0.5f, -0.5f, 0.0f,
            +0.5f, -0.5f, 0.0f,
    };

    std::vector<unsigned int> indices = {
            0, 1, 2,
            1, 3, 2
    };

public:
    Sandbox()
            : Application("Sandbox", 800, 600),
              sourceCode(Crayon::ResourceLoader::LoadFileAsString("assets/shaders/basic.glsl")),
              shader(sourceCode)
    {
        GLCall(glClearColor(0.2f, 0.4f, 0.6f, 1.0f));

        // Vertex Array
        GLCall(glGenVertexArrays(1, &vao));
        GLCall(glBindVertexArray(vao));

        // Vertex Buffer
        GLCall(glGenBuffers(1, &vbo));
        GLCall(glBindBuffer(GL_ARRAY_BUFFER, vbo));
        GLCall(glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices[0], GL_STATIC_DRAW));

        // Link to VA
        GLCall(glEnableVertexAttribArray(0));
        GLCall(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (const void*)0));

        // Index Buffer
        GLCall(glGenBuffers(1, &ibo));
        GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo));
        GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW));

        // SHADER
        CRAYON_TRACE("Shader source code:\n{}", sourceCode);
        shader.Bind();

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

        GLCall(glBindVertexArray(vao));
        GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo));
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