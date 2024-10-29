#pragma once

#include "Core/OpenGL.h"
#include "Crayon/Utils/ResourceLoader.h"

namespace Crayon::Graphics
{
    class Shader
    {
    private:
        unsigned int m_Program; // Shader Program memory address
        std::map<std::string, int> m_UniformCache;

    public:
        // CONSTRUCTOR & DESTRUCTOR

        Shader(std::vector<std::string> &shaderPaths)
        {
            this->m_Program = Shader::CompileProgram(shaderPaths);
            this->m_UniformCache = std::map<std::string, int>();
        }

        ~Shader()
        {
            GLCall(glDeleteProgram(this->m_Program));
        }

        // METHODS

        void Bind() const
        {
            GLCall(glUseProgram(this->m_Program));
        }

        void Unbind() const
        {
            GLCall(glUseProgram(0));
        }

        // GETTERS

        bool IsBound() const
        {
            GLint program;
            glGetIntegerv(GL_CURRENT_PROGRAM, &program);
            return m_Program == program;
        }

        // UNIFORMS

    private:
        int GetUniformLocation(const std::string &name)
        {
            // Checking if uniform location is cached...
            if (m_UniformCache.contains(name))
            {
                return m_UniformCache.at(name);
            }

            // Binding shader to search through...
            if (!this->IsBound())
            {
                this->Bind();
                CRAYON_CORE_WARN("Shaders should be bound before setting a uniform!");
            }

            // Searching location...
            int location = glGetUniformLocation(this->m_Program, name.c_str());

            if (location == -1)
            {
                // Not found...
                CRAYON_CORE_ERROR("Unable to find uniform: {}", name);
            }
            else
            {
                // Caching...
                m_UniformCache.insert_or_assign(name, location);
            }

            return location;
        }

    public:
        void SetUniform1i(const std::string &name, const int data)
        {
            int location = this->GetUniformLocation(name);
            glUniform1i(location, data);
        }

        void SetUniform1f(const std::string &name, const float &data)
        {
            int location = this->GetUniformLocation(name);
            glUniform1f(location, data);
        }

        void SetUniform2f(const std::string &name, const glm::vec2 &data)
        {
            int location = this->GetUniformLocation(name);
            glUniform2f(location, data.x, data.y);
        }

        void SetUniform3f(const std::string &name, const glm::vec3 &data)
        {
            int location = this->GetUniformLocation(name);
            glUniform3f(location, data.x, data.y, data.z);
        }

        void SetUniform4f(const std::string &name, const glm::vec4 &data)
        {
            int location = this->GetUniformLocation(name);
            glUniform4f(location, data.x, data.y, data.z, data.w);
        }

        void SetUniformMatrix2f(const std::string &name, const glm::mat2 &data)
        {
            int location = this->GetUniformLocation(name);
            glUniformMatrix2fv(location, 1, GL_FALSE, &data[0][0]);
        }

        void SetUniformMatrix3f(const std::string &name, const glm::mat3 &data)
        {
            int location = this->GetUniformLocation(name);
            glUniformMatrix3fv(location, 1, GL_FALSE, &data[0][0]);
        }

        void SetUniformMatrix4f(const std::string &name, const glm::mat4 &data)
        {
            int location = this->GetUniformLocation(name);
            glUniformMatrix4fv(location, 1, GL_FALSE, &data[0][0]);
        }

    private:
        static unsigned int CompileProgram(std::vector<std::string> &shaderPaths)
        {
            // Creating program
            unsigned int shaderProgram = glCreateProgram();

            // Compiling and attaching shaders
            int shaderTypesCount = 0;
            unsigned int *shaders = new unsigned int[shaderTypesCount];
            for (const auto &shaderPath : shaderPaths)
            {
                CRAYON_CORE_TRACE("Compiling shader at: {}", shaderPath);

                // Getting shader type
                std::string extension = shaderPath.substr(shaderPath.find_last_of('.') + 1);
                GLenum shaderType;

                if (extension == "vert")
                {
                    shaderType = GL_VERTEX_SHADER;
                }
                else if (extension == "frag")
                {
                    shaderType = GL_FRAGMENT_SHADER;
                }
                else
                {
                    CRAYON_CORE_ERROR("The {} file extension for shaders is not yet supported!", extension);
                }

                // Getting shader code
                const std::string &shaderCode = ResourceLoader::LoadFileAsString(shaderPath);

                // Compiling shader
                unsigned int shader = CompileShader(shaderType, shaderCode.c_str());
                GLCall(glAttachShader(shaderProgram, shader));

                shaderTypesCount++;
            }

            // Compiling program
            GLCall(glLinkProgram(shaderProgram));

            // Checking for errors
            int status;
            GLCall(glGetProgramiv(shaderProgram, GL_LINK_STATUS, &status));
            if (status == GL_FALSE)
            {
                int length;
                GLCall(glGetProgramiv(shaderProgram, GL_INFO_LOG_LENGTH, &length));

                char *message = (char *)alloca(length * sizeof(char));
                GLCall(glGetProgramInfoLog(shaderProgram, length, &length, message));

                spdlog::error("Failed to compile program! -> {}", message);
            }

            GLCall(glValidateProgram(shaderProgram)); // Validating program

            // Deleting shaders
            for (int i = 0; i < shaderTypesCount; i++)
            {
                GLCall(glDeleteShader(shaders[i]));
            }

            delete[] shaders;

            return shaderProgram;
        }

        static unsigned int CompileShader(const GLenum type, const char *shaderCode)
        {
            // Creating shader
            unsigned int shader = glCreateShader(static_cast<GLenum>(type));
            GLCall(glShaderSource(shader, 1, &shaderCode, nullptr)); // Linking source code

            // Compiling shader
            GLCall(glCompileShader(shader));

            // Checking for errors
            int result;
            GLCall(glGetShaderiv(shader, GL_COMPILE_STATUS, &result));
            if (result == GL_FALSE)
            {
                int length;
                GLCall(glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length));

                char *message = (char *)alloca(length * sizeof(char));
                GLCall(glGetShaderInfoLog(shader, length, &length, message));

                CRAYON_CORE_ERROR(message);
            }
            else
            {
                CRAYON_CORE_TRACE("Shader compiled successfully!");
            }

            return shader;
        }
    };
}