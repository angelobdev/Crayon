#include "Crayon.h"

class Sandbox : public Crayon::Application
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

    std::unique_ptr<Crayon::VertexArray> vertexArray;
    std::unique_ptr<Crayon::VertexBuffer<float>> vertexBuffer;
    std::unique_ptr<Crayon::IndexBuffer> indexBuffer;
    std::unique_ptr<Crayon::Shader> shader;
    std::unique_ptr<Crayon::Texture> texture;

    glm::vec3 obj_position = glm::vec3(0.0f, 0.0f, -2.0f);
    glm::vec3 cam_position = glm::vec3(0.0f, 0.0f, 0.0f);

public:
    Sandbox() : Application("Sandbox", 800, 600)
    {
        GLCall(glClearColor(0.2f, 0.4f, 0.6f, 1.0f));

        vertexArray = std::make_unique<Crayon::VertexArray>();
        vertexArray->Bind();

        vertexBuffer = std::make_unique<Crayon::VertexBuffer<float>>(vertices, std::vector<Crayon::VertexLayout>({{3, GL_FLOAT},
                                                                                                                  {3, GL_FLOAT},
                                                                                                                  {2, GL_FLOAT}}));
        indexBuffer = std::make_unique<Crayon::IndexBuffer>(indices);
        shader = std::make_unique<Crayon::Shader>("assets/shaders/basic.glsl", true);
        texture = std::make_unique<Crayon::Texture>("assets/textures/test.png");
    }

    void Update(double deltaTime) override
    {
        if (Crayon::Input::GetKeyDown(GLFW_KEY_W))
            cam_position.z += 1.0f * deltaTime;
        if (Crayon::Input::GetKeyDown(GLFW_KEY_S))
            cam_position.z -= 1.0f * deltaTime;
        if (Crayon::Input::GetKeyDown(GLFW_KEY_A))
            cam_position.x += 1.0f * deltaTime;
        if (Crayon::Input::GetKeyDown(GLFW_KEY_D))
            cam_position.x -= 1.0f * deltaTime;
        if (Crayon::Input::GetKeyDown(GLFW_KEY_LEFT_SHIFT))
            cam_position.y += 1.0f * deltaTime;
        if (Crayon::Input::GetKeyDown(GLFW_KEY_SPACE))
            cam_position.y -= 1.0f * deltaTime;
    }

    void Render() override
    {
        GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

        shader->Bind();

        shader->SetUniformMatrix4f("u_Model", glm::translate(glm::mat4(1.0f), obj_position));
        shader->SetUniformMatrix4f("u_View", glm::translate(glm::mat4(1.0f), cam_position));

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