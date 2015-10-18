#pragma once
#include <GL/glew.h>

class FrameBuffer
{

public:

    FrameBuffer(int width, int height);

    void bindForWriting() const;
    void bindForReading(GLenum textureUnit) const;

private:

    void checkStatus() const;

    GLuint fbo;
    GLuint texture;
};
