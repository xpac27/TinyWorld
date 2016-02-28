#pragma once
#include "ProgramParams.hpp"
#include "Shader.hpp"
#include <OpenGL.hpp>

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
#ifdef PLATFORM_OSX
    Shader gs;
#endif
    Shader fs;

    void link() const;

};
