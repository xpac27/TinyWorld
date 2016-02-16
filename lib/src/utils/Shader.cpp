#include "Shader.hpp"
#include "log.hpp"
#include "../../inc/utils/Program.hpp"
#include <fstream>

using namespace std;

Shader::Shader(GLuint _type, Program* _program)
    : reference(glCreateShader(_type))
    , program(_program)
{}

Shader::~Shader()
{
    glDetachShader(program->getReference(), reference);
    glDeleteShader(reference);
}

void Shader::read(const char* filename)
{
    ifstream file(filename, ifstream::in);
    if (file.is_open()) {
        string content, line = "";
        while(!file.eof()) {
            getline(file, line);
            content.append(line + "\n");
        }
        const GLchar* p[1] = {content.data()};
        GLint l[1] = {GLint(content.size())};
        glShaderSource(reference, 1, p, l);
    } else {
        error("ERROR: cannot open", filename);
    }
}

void Shader::compile()
{
    GLint result;
    glCompileShader(reference);
    glGetShaderiv(reference, GL_COMPILE_STATUS, &result);
    if (result == 0) {
        GLchar Infolog[1024];
        glGetShaderInfoLog(reference, sizeof(Infolog), NULL, Infolog);
        error(Infolog);
    } else {
        glAttachShader(program->getReference(), reference);
    }
}
