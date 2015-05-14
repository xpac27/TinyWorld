#pragma once
#include <GL/glew.h>

class Program;

class Shader
{

public:

    Shader(GLuint _type, Program* _program);
    ~Shader();

    void read(const char* filename);
    void compile();

private:

    GLuint reference;
    Program* program;
};
