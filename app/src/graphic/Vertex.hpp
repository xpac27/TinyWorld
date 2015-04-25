#pragma once
#include <GL/glew.h>

struct Vertex
{
    GLfloat x {0.f};
    GLfloat y {0.f};
    GLfloat z {0.f};

    Vertex(GLfloat _x, GLfloat _y, GLfloat _z)
        : x(_x), y(_y), z(_z)
    {}
};
