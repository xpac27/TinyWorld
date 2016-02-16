#include "Program.hpp"
#include "Shader.hpp"
#include "../utils/log.hpp"

Program::Program()
    : reference(glCreateProgram())
{}

Program::Program(const char* vertexShaderFilePath, const char* fragmentShaderFilePath) : Program()
{
    Shader vs(GL_VERTEX_SHADER, reference, vertexShaderFilePath);
    Shader fs(GL_FRAGMENT_SHADER, reference, fragmentShaderFilePath);
    link();
}

Program::Program(const char* vertexShaderFilePath, const char* geometryShaderFilePath, const char* fragmentShaderFilePath) : Program()
{
    Shader vs(GL_VERTEX_SHADER, reference, vertexShaderFilePath);
    Shader gs(GL_GEOMETRY_SHADER, reference, geometryShaderFilePath);
    Shader fs(GL_FRAGMENT_SHADER, reference, fragmentShaderFilePath);
    link();
}

Program::~Program()
{
    glDeleteProgram(reference);
}

void Program::use() const
{
    glUseProgram(reference);
}

void Program::idle() const
{
    glUseProgram(0);
}

GLint Program::getLocation(const char* variable) const
{
    return glGetUniformLocation(reference, variable);
}

void Program::link() const
{
    GLint result;
    glLinkProgram(reference);
    glGetProgramiv(reference, GL_LINK_STATUS, &result);
    if (result == 0) {
        GLchar Errorlog[1024];
        glGetProgramInfoLog(reference, sizeof(Errorlog), NULL, Errorlog);
        error(Errorlog);
    } else {
        glValidateProgram(reference);
    }
}
