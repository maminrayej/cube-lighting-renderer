#include <string>
#include <stdexcept>
#include <glad/glad.h>

using std::string;

namespace shader {
    string getShaderString(GLenum shaderType) {
        if (shaderType == GL_VERTEX_SHADER) {
            return string{"vertex shader"};
        } else {
            return string{"fragment shader"};
        }
    }

    unsigned int compileShader(GLenum shaderType, const string &shaderSource) {
        unsigned int shader = glCreateShader(shaderType);
        const char *shaderSourceStr = shaderSource.c_str();
        glShaderSource(shader, 1, &shaderSourceStr, nullptr);
        glCompileShader(shader);

        int success{};
        char infoLog[512]{};
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(shader, 512, nullptr, infoLog);
            glDeleteShader(shader);
            throw std::runtime_error{"Failed to compile " + getShaderString(shaderType) + ": " + string{infoLog}};
        }

        return shader;
    }

    void deleteShader(unsigned int shader) {
        glDeleteShader(shader);

        int success{};
        char infoLog[512]{};
        glGetShaderiv(shader, GL_DELETE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(shader, 512, nullptr, infoLog);
            throw std::runtime_error{"Failed to delete shader with id: " + std::to_string(shader)};
        }
    }

    void deleteProgram(unsigned int program) {
        glDeleteProgram(program);

        int success{};
        char infoLog[512]{};
        glGetProgramiv(program, GL_DELETE_STATUS, &success);
        if (!success) {
            glad_glGetProgramInfoLog(program, 512, nullptr, infoLog);
            throw std::runtime_error{"Failed to delete program with id: " + std::to_string(program)};
        }
    }
}