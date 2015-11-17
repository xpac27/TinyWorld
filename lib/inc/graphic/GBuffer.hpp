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

    // TODO auto detect screen size
    int SCR_WIDTH = 800;
    int SCR_HEIGHT = 600;

    GLuint gBuffer;
    GLuint gPosition;
    GLuint gNormal;
    GLuint gAlbedoSpec;
};
