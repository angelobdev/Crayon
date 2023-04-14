#pragma once

/**************************************************************************************************
 * @file JAGL/Graphics/Shader.h
 * @brief Shader class header file.
 * @details This file implements the Shader wrapper class structure.
 **************************************************************************************************
 * @author angelobdev
 * @date 01-27-2023
 ***************************************************************************************************/

#include "Common.h"

namespace Crayon
{
    class Shader
    {
    private:
        unsigned int m_Program; // Shader Program memory address
        // TODO: Caching for uniforms

    public:
        /// @brief Generates a new OpenGL shader program from a glsl file
        /// @param shaderFilePath File location
        Shader(const std::string &sourceCode, bool isPath = true);

        ~Shader();

    public:
        /* ***** CLASS METHODS ***** */

        /// @brief Binds the current Shader Program
        void Bind() const;

        /// @brief Unbinds the current Shader Program
        void Unbind() const;

        /* ***** SHADER UNIFORMS ***** */

        /// @brief Returns the location of the specified uniform
        /// @param name Name of the uniform used in the glsl file
        /// @return Location of the uniform
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
        /* ***** CLASS UTILITIES ***** */
        static std::string GetShaderSourceCode(const GLenum &type, const char *sourceCode);
        static unsigned int CompileProgram(const char *sourceCode);
        static unsigned int CompileShader(GLenum type, const char *shaderSourceCode);
    };
}