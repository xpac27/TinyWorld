#pragma once
#include <GL/glew.h>

class Shader
{

public:

    Shader(GLuint _type, GLuint _programReference, const char* filename);
    ~Shader();

private:

    GLuint reference;
    GLuint programReference;
};
