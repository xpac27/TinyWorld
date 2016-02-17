#pragma once
#include <GL/glew.h>

class Quad
{

public:

    Quad();

    void draw();

private:

    GLuint quadVAO;
    GLuint quadVBO;
};
