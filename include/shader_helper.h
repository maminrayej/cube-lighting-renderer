#ifndef OPENGL_SHADER_HELPER_H
#define OPENGL_SHADER_HELPER_H

#include <string>
#include <glad/glad.h>

using std::string;

namespace shader {
    string getShaderString(GLenum shaderType);

    unsigned int compileShader(GLenum shaderType, const string &shaderSource);

    void deleteShader(unsigned int shader);

    void deleteProgram(unsigned int program);
}


#endif //OPENGL_SHADER_HELPER_H
