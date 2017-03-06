#include "Program.hpp"
#include "../../inc/utils/Utility.hpp"
#include "../utils/Log.hpp"

Program::Program(ProgramParams params)
    : reference(glCreateProgram())
    , vs(GL_VERTEX_SHADER, reference)
    , gs(GL_GEOMETRY_SHADER, reference)
    , fs(GL_FRAGMENT_SHADER, reference)
{
    if (!isEmpty(params.vertexShader)) {
        vs.load(params.vertexShader);
    }
    if (!isEmpty(params.geometryShader)) {
        gs.load(params.geometryShader);
    }
    if (!isEmpty(params.fragmentShader)) {
        fs.load(params.fragmentShader);
    }
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
