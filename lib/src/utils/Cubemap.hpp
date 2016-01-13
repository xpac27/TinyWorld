#pragma once
#include <GL/glew.h>
#include <vector>

class Cubemap
{

public:

    ~Cubemap();

    void load(const std::vector<const char*> filenames);
    void bind(GLuint textureUnit);

private:

    void destroy();

    bool loaded = false;

    GLuint id;
};
