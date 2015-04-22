#pragma once
#include <GL/glew.h>

struct Normal
{
    GLfloat x {0.f};
    GLfloat y {0.f};
    GLfloat z {0.f};

    Normal(GLfloat _x, GLfloat _y, GLfloat _z)
        : x(_x), y(_y), z(_z)
    {}
};

