#pragma once
#include <GL/glew.h>

class Quad
{

public:

    void initialize();
    void draw();

private:

    GLuint quadVAO;
    GLuint quadVBO;
};
