#pragma once
#include <GL/glew.h>

class Texture
{

public:

    ~Texture();

    void load(const char *filename);
    void bind(GLuint textureUnit);

private:

    bool loaded = false;

    GLuint id;
};
