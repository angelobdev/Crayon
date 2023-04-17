#pragma once

#include "Crayon/Graphics/Common.h"

namespace Crayon
{
    class Shader
    {
    private:
        unsigned int m_Program; // Shader Program memory address
        // TODO: Caching for uniforms

    public:
        // CONSTRUCTOR & DESTRUCTOR

        Shader(const std::string &sourceCode, bool isPath = true);

        ~Shader();

        // METHODS

        void Bind() const;

        void Unbind() const;

        // GETTERS

        bool IsBound() const;

        // UNIFORMS

        int GetUniformLocation(const std::string &name) const;

        void SetUniform1i(const std::string &name, const int data) const; // Used for sampler2D

        void SetUniform1f(const std::string &name, const float &data) const;

        void SetUniform2f(const std::string &name, const glm::vec2 &data) const;

        void SetUniform3f(const std::string &name, const glm::vec3 &data) const;

        void SetUniform4f(const std::string &name, const glm::vec4 &data) const;

        void SetUniformMatrix2f(const std::string &name, const glm::mat2 &data) const;

        void SetUniformMatrix3f(const std::string &name, const glm::mat3 &data) const;

        void SetUniformMatrix4f(const std::string &name, const glm::mat4 &data) const;

    private:

        // UTILITIES

        static std::string GetShaderSourceCode(const GLenum &type, const char *sourceCode);

        static unsigned int CompileProgram(const char *sourceCode);

        static unsigned int CompileShader(GLenum type, const char *shaderSourceCode);
    };
}