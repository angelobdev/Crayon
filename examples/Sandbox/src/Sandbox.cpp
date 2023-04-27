#include "Crayon.h"

class Sandbox : public Crayon::Application
{
private:
    std::vector<float> vertices = {
            // POSITION         // COLOR         // TEXTURE COORD
            -0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
            +0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
            -0.5f, +0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
            +0.5f, +0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
    };

    std::vector<unsigned int> indices = {
            0, 1, 2,
            1, 3, 2
    };

    Crayon::VertexArray vertexArray;
    Crayon::VertexBuffer vertexBuffer;
    Crayon::IndexBuffer indexBuffer;
    Crayon::Shader shader;
    Crayon::Texture texture;

    glm::vec3 obj_position = glm::vec3(0.0f, 0.0f, -2.0f);
    glm::vec3 cam_position = glm::vec3(0.0f, 0.0f, 0.0f);

public:
    Sandbox() : Application("Sandbox", 800, 600),
                vertexArray(),
                vertexBuffer(vertices),
                indexBuffer(indices),
                shader("assets/shaders/basic.glsl", true),
                texture("assets/textures/test.png")
    {
        GLCall(glClearColor(0.2f, 0.4f, 0.6f, 1.0f));

        // Linking Vertex Buffer to Vertex Array
        vertexArray.LinkBuffer(vertexBuffer,
                               Crayon::VertexLayout({
                                                            {3, GL_FLOAT},
                                                            {3, GL_FLOAT},
                                                            {2, GL_FLOAT}
                                                    }));

    }

    void Update() override
    {
        if(Crayon::Input::GetKey(GLFW_KEY_W) == Crayon::KeyState::)
    }

    void Render() override
    {
        GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

        shader.Bind();

        shader.SetUniformMatrix4f("u_Model", glm::translate(glm::mat4(1.0f), obj_position));
        shader.SetUniformMatrix4f("u_View", glm::translate(glm::mat4(1.0f), cam_position));

        shader.SetUniformMatrix4f
                ("u_Projection",
                 glm::perspective
                         (
                                 glm::radians(70.0f),
                                 m_Window->GetAspectRatio(),
                                 1.0f,
                                 100.0f
                         )
                );

        texture.Bind(1);
        shader.SetUniform1i("u_Texture", 1);

        vertexArray.Bind();
        indexBuffer.Bind();

        GLCall(glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, nullptr));

        indexBuffer.Unbind();
        vertexArray.Unbind();

        shader.Unbind();
    }

    void RenderUI() override
    {
        // UI RENDERING
        ImGui::Begin("Controller");
        ImGui::SliderFloat3("Camera Position", &cam_position.x, -10.0f, 10.0f);
        ImGui::SliderFloat3("Object Position", &obj_position.x, -10.0f, 10.0f);
        ImGui::End();
    }

    ~Sandbox() override
    {

    }

};

Crayon::Application *Crayon::CreateApplication()
{
    return new Sandbox();
}