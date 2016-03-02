#pragma once
#include <OpenGL.hpp>

class Shader
{

public:

    Shader(GLuint _type, GLuint _programReference);
    ~Shader();

    void load(const char* filename);

private:

    GLuint reference;
    GLuint programReference;
};
