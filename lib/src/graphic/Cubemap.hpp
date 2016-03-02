#pragma once
#include <graphic/CubemapParams.hpp>
#include <OpenGL.hpp>
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
