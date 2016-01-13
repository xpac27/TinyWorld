#pragma once
#include <GL/glew.h>

class GBuffer
{

public:

    void initialize();
    void bindTextures(GLuint textureUnit1, GLuint textureUnit2, GLuint textureUnit3);
    void bind();
    void idle();

private:

    GLuint gBuffer;
    GLuint gPosition;
    GLuint gNormal;
    GLuint gAlbedoSpec;
};
