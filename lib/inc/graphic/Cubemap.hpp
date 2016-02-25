#pragma once
#include "CubemapParams.hpp"
#include <GL/glew.h>
#include <vector>

class Cubemap
{

public:

    Cubemap(CubemapParams params);
    ~Cubemap();

    void bind(GLuint textureUnit);

private:

    GLuint id;
};
