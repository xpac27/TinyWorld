#include "SBuffer.hpp"
#include "../utils/log.hpp"

void SBuffer::initialize()
{
    // TODO get windows size from conf
    int SCR_WIDTH = 1024 / 4;
    int SCR_HEIGHT = 768 / 4;

    glGenFramebuffers(1, &sBuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, sBuffer);

    // - Shadow buffer
    glGenTextures(1, &sShadow);
    glBindTexture(GL_TEXTURE_2D, sShadow);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB4, SCR_WIDTH, SCR_HEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, sShadow, 0);

    // - Tell OpenGL which color attachments we'll use (of this framebuffer) for rendering
    GLuint attachments[1] = { GL_COLOR_ATTACHMENT0 };
    glDrawBuffers(1, attachments);

    // - Create and attach depth buffer (renderbuffer)
    GLuint rboDepth;
    glGenRenderbuffers(1, &rboDepth);
    glBindRenderbuffer(GL_RENDERBUFFER, rboDepth);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, SCR_WIDTH, SCR_HEIGHT);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rboDepth);

    // - Finally check if framebuffer is complete
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        error("Framebuffer failed for SBuffer!");
    }
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void SBuffer::bindTextures(GLuint shadow)
{
    glActiveTexture(shadow);
    glBindTexture(GL_TEXTURE_2D, sShadow);
}

void SBuffer::bind()
{
    glBindFramebuffer(GL_FRAMEBUFFER, sBuffer);
}

void SBuffer::idle()
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
