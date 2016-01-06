#include "utils/Program.hpp"
#include "utils/Log.hpp"

using namespace Log;

Program::Program()
    : reference(glCreateProgram())
{}

Program::~Program()
{
    glDeleteProgram(reference);
}

GLuint Program::getReference()
{
    return reference;
}

GLint Program::getLocation(const char* variable)
{
    return glGetUniformLocation(reference, variable);
}

void Program::link()
{
    GLint result;
    glLinkProgram(reference);
    glGetProgramiv(reference, GL_LINK_STATUS, &result);
    if (result == 0) {
        GLchar ErrorLog[1024];
        glGetProgramInfoLog(reference, sizeof(ErrorLog), NULL, ErrorLog);
        error(ErrorLog);
    } else {
        glValidateProgram(reference);
    }
}

void Program::use()
{
    glUseProgram(reference);
}

void Program::idle()
{
    glUseProgram(0);
}
