#pragma once

#include "Common.h"

namespace Crayon
{
    class Shader
    {
    private:
        unsigned int m_ProgramID;

    public:

        // Constructor & Destructor

        Shader(const std::string &sourceCode);

        ~Shader()
        {}

        // Methods

        void Bind() const;

        void Unbind() const;

    private:

        // Utilities

        static std::string GetShaderSourceCode(const GLenum &type, const char *sourceCode);

        unsigned int CompileProgram(const char *sourceCode);

        unsigned int CompileShader(GLenum type, const char *shaderSourceCode);

    };
}