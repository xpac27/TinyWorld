#pragma once
#include <GL/glew.h>

class GBuffer
{

public:

    void initialize();
    void bindTextures();
    void bind();
    void idle();

private:

    GLuint gBuffer;
    GLuint gPosition;
    GLuint gNormal;
    GLuint gAlbedoSpec;
};
