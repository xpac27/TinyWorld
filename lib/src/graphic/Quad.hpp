#pragma once
#include <OpenGL.hpp>

class Quad
{

public:

    Quad();

    void draw();

private:

    GLuint quadVAO;
    GLuint quadVBO;
};
