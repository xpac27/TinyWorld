#pragma once
#include <OpenGL.hpp>

class GBuffer
{

public:

    GBuffer();

    void bindTextures(GLuint position, GLuint normal, GLuint diffuse, GLuint MRS, GLuint shadow);
    void bind();
    void idle();

private:

    GLuint gBuffer;
    GLuint gPosition;
    GLuint gNormal;
    GLuint gDiffuse;
    GLuint gMR;
    GLuint gShadow;
};
