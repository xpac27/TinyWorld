#pragma once
#include <GL/glew.h>

class SBuffer
{

public:

    void initialize();
    void bindTextures(GLuint shadows);
    void bind();
    void idle();

private:

    GLuint sBuffer;
    GLuint sShadow;
};
