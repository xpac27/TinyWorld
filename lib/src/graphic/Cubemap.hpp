#pragma once
#include <GL/glew.h>
#include <vector>

class Cubemap
{

public:

    Cubemap(const char* filenames[6]);
    ~Cubemap();

    void bind(GLuint textureUnit);

private:

    GLuint id;
};
