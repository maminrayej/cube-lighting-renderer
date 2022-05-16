#ifndef OPENGL_SHADER_PROGRAM_H
#define OPENGL_SHADER_PROGRAM_H

#include <string>
#include <array>

#include <glm/glm.hpp>

using std::string;
using std::array;

namespace shader {
    class ShaderProgram {
    private:
        unsigned int shaderProgram;

    public:
        ShaderProgram(const string &vertexShaderSource, const string &fragmentShaderSource);

        void useProgram() const;

        [[nodiscard]] int getUniformLocation(const string& name) const;

        template<size_t N>
        void setUniform(const string& name, const array<int, N>& values) const;

        template<size_t N>
        void setUniform(const string& name, const array<float, N>& values) const;

        void setUniform(const string& name, const glm::mat4& mat) const;

        [[nodiscard]] unsigned int getProgramId() const;
    };
}

#include "shader_program.inl"

#endif //OPENGL_SHADER_PROGRAM_H
