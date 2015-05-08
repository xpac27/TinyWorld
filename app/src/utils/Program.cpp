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

void Program::link()
{
    GLint success;
    glLinkProgram(reference);
    glGetProgramiv(reference, GL_LINK_STATUS, &success);
    if (success == 0) {
        GLchar ErrorLog[1024];
        glGetProgramInfoLog(reference, sizeof(ErrorLog), NULL, ErrorLog);
        printl(ErrorLog);
    } else {
        glValidateProgram(reference);
    }
}

void Program::use()
{
    glUseProgram(reference);
}

GLint Program::getLocation(const char* variable)
{
    return glGetUniformLocation(reference, variable);
}
