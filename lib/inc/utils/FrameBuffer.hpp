#pragma once
#include <GL/glew.h>

class FrameBuffer
{

public:

    ~FrameBuffer();

    void initialize(int width, int height);
    void bindForWriting() const;
    void bindForReading(GLuint textureUnit) const;
    void idle() const;

private:

    void checkStatus() const;

    GLuint fbo;
    GLuint texture;
    GLuint m_DepthBuffer;
};
