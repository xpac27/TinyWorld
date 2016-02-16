#pragma once
#include <GL/glew.h>

class Program
{

public:

    Program();
    ~Program();

    GLuint getReference();
    GLint getLocation(const char* variable);

    void link();
    void use();
    void idle();

private:

    GLuint reference;

};
