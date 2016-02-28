#pragma once
#include "ProgramParams.hpp"
#include "Shader.hpp"
#include <GL/glew.h>

class Program
{

public:

    // TODO pass file objects instead of file paths
    Program(ProgramParams params);

    ~Program();

    void use() const;
    void idle() const;

    GLint getLocation(const char* variable) const;

private:

    Program();

    GLuint reference;

    Shader vs;
    Shader gs;
    Shader fs;

    void link() const;

};
