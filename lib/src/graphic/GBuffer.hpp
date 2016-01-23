#pragma once
#include <GL/glew.h>

class GBuffer
{

public:

    void initialize();
    void bindTextures(GLuint position, GLuint normal, GLuint diffuse, GLuint MRAO);
    void bind();
    void idle();

private:

    GLuint gBuffer;
    GLuint gPosition;
    GLuint gNormal;
    GLuint gDiffuse;
    GLuint gMRAO;
};
