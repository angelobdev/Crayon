#include "Shader.h"

namespace Crayon
{
    Shader::Shader(const std::string &sourceCode)
    {
        this->m_ProgramID = CompileProgram(sourceCode.c_str());
    }

    void Shader::Bind() const
    {
        GLCall(glUseProgram(this->m_ProgramID));
    }

    void Shader::Unbind() const
    {
        GLCall(glUseProgram(0));
    }

    std::string Shader::GetShaderSourceCode(const GLenum &type, const char *sourceCode)
    {
        // Getting type breakpoint
        std::string breakpoint;
        switch (type)
        {
            case GL_VERTEX_SHADER:
                breakpoint = "VERTEX";
                break;
            case GL_FRAGMENT_SHADER:
                breakpoint = "FRAGMENT";
                break;
            default:
                spdlog::error("Unable to parse shader of this type");
                break;
        }

        // Parsing sourceCode
        std::stringstream content;
        std::istringstream sourceCodeStream(sourceCode);

        std::string line;
        bool write = false;
        while (std::getline(sourceCodeStream, line))
        {
            if (write)
            {
                if (line.find("END") != std::string::npos)
                    break;

                // Writing
                content << line << std::endl;
            }

            if (line.find(breakpoint) != std::string::npos)
                write = true;
        }

        // Retuning shader content
        return content.str();
    }

    unsigned int Shader::CompileProgram(const char *sourceCode)
    {
        // Creating program
        unsigned int shaderProgram = glCreateProgram();

        // Creating Vertex Shader
        unsigned int vs = CompileShader(GL_VERTEX_SHADER,
                                        Shader::GetShaderSourceCode(GL_VERTEX_SHADER, sourceCode).c_str());
        GLCall(glAttachShader(shaderProgram, vs));

        // Creating fragment shader
        unsigned int fs = CompileShader(GL_FRAGMENT_SHADER,
                                        Shader::GetShaderSourceCode(GL_FRAGMENT_SHADER, sourceCode).c_str());
        GLCall(glAttachShader(shaderProgram, fs));

        // Compiling program
        GLCall(glLinkProgram(shaderProgram));

        // Checking for errors
        int status;
        GLCall(glGetProgramiv(shaderProgram, GL_LINK_STATUS, &status));
        if (status == GL_FALSE)
        {
            int length;
            GLCall(glGetProgramiv(shaderProgram, GL_INFO_LOG_LENGTH, &length));

            char *message = (char *) alloca(length * sizeof(char));
            GLCall(glGetProgramInfoLog(shaderProgram, length, &length, message));

            spdlog::error("Failed to compile program! -> {}", message);
        }

        GLCall(glValidateProgram(shaderProgram)); // Validating program

        // Deleting shaders
        GLCall(glDeleteShader(vs));
        GLCall(glDeleteShader(fs));

        return shaderProgram;
    }

    unsigned int Shader::CompileShader(GLenum type, const char *shaderSourceCode)
    {
        // Creating shader
        unsigned int shader = glCreateShader(type);
        GLCall(glShaderSource(shader, 1, &shaderSourceCode, nullptr)); // Linking source code

        // Compiling shader
        GLCall(glCompileShader(shader));

        // Checking for errors
        int result;
        GLCall(glGetShaderiv(shader, GL_COMPILE_STATUS, &result));
        if (result == GL_FALSE)
        {
            int length;
            GLCall(glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length));

            char *message = (char *) alloca(length * sizeof(char));
            GLCall(glGetShaderInfoLog(shader, length, &length, message));

            spdlog::error(message); // Logging error if necessary
        }

        return shader;
    }

}