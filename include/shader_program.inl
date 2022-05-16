#ifndef OPENGL_SHADER_PROGRAM_IMPL_H
#define OPENGL_SHADER_PROGRAM_IMPL_H

#include <string>
#include <stdexcept>

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>
#include <glm/glm.hpp>

#include "shader_program.h"
#include "shader_helper.h"

using std::string;

namespace shader {
    ShaderProgram::ShaderProgram(const string &vertexShaderSource, const string &fragmentShaderSource) {
        unsigned int vertexShader = compileShader(GL_VERTEX_SHADER, vertexShaderSource);
        unsigned int fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragmentShaderSource);

        shaderProgram = glCreateProgram();

        glAttachShader(shaderProgram, vertexShader);
        glAttachShader(shaderProgram, fragmentShader);

        glLinkProgram(shaderProgram);

        int success{};
        char infoLog[512]{};
        glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);

            // Delete program and its shaders to free up resources
            deleteShader(vertexShader);
            deleteShader(fragmentShader);
            deleteProgram(shaderProgram);

            throw std::runtime_error{"Failed to link shader program: " + string{infoLog}};
        }

        // Delete shaders after a successful linkage of the program to free up resources
        deleteShader(vertexShader);
        deleteShader(fragmentShader);
    }

    void ShaderProgram::useProgram() const {
        glUseProgram(shaderProgram);
    }

    int ShaderProgram::getUniformLocation(const string& name) const {
        return glGetUniformLocation(shaderProgram, name.c_str());
    }

    template<size_t N>
    void ShaderProgram::setUniform(const string& name, const array<int, N>& values) const {
        int loc = getUniformLocation(name);

        if (loc == -1) {
            throw std::runtime_error{"Uniform name is invalid"};
        }

        if (N == 1) {
            glUniform1i(loc, values[0]);
        } else if (N == 2) {
            glUniform2i(loc, values[0], values[1]);
        } else if (N == 3) {
            glUniform3i(loc, values[0], values[1], values[2]);
        } else if (N == 4) {
            glUniform4i(loc, values[0], values[1], values[2], values[3]);
        }
    }

    template<size_t N>
    void ShaderProgram::setUniform(const string& name, const array<float, N>& values) const {
        int loc = getUniformLocation(name);

        if (loc == -1) {
            throw std::runtime_error{"Uniform name is invalid"};
        }

        if (N == 1) {
            glUniform1f(loc, values[0]);
        } else if (N == 2) {
            glUniform2f(loc, values[0], values[1]);
        } else if (N == 3) {
            glUniform3f(loc, values[0], values[1], values[2]);
        } else if (N == 4) {
            glUniform4f(loc, values[0], values[1], values[2], values[3]);
        }
    }

    void ShaderProgram::setUniform(const string &name, const glm::mat4 &mat) const {
        int loc = getUniformLocation(name);

        if (loc == -1) {
            throw std::runtime_error{"Uniform name is invalid"};
        }

        glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(mat));
    }

    unsigned int ShaderProgram::getProgramId() const {
        return shaderProgram;
    }
}

#endif //OPENGL_SHADER_PROGRAM_IMPL_H
