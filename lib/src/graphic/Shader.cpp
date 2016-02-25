#include "../../inc/graphic/Shader.hpp"
#include "../utils/log.hpp"
#include <fstream>

using namespace std;

Shader::Shader(GLuint _type, GLuint _programReference)
    : reference(glCreateShader(_type))
    , programReference(_programReference)
{
}

void Shader::load(const char* filename)
{
    // Read
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

        // Compile
        GLint result;
        glCompileShader(reference);
        glGetShaderiv(reference, GL_COMPILE_STATUS, &result);
        if (result == 0) {
            GLchar Infolog[1024];
            glGetShaderInfoLog(reference, sizeof(Infolog), NULL, Infolog);
            error(Infolog);
        } else {
            glAttachShader(programReference, reference);
            success("Shader loaded:", filename);
        }
    } else {
        error("Cannot open", filename);
    }
}

Shader::~Shader()
{
    glDetachShader(programReference, reference);
    glDeleteShader(reference);
}
