#include "Texture.hpp"
#include "PNG.hpp"
#include <string>

using namespace std;

void Texture::load(const char *filename)
{
    if (filename && !filename[0]) return;
    if (loaded) destroy();

    PNG png(filename);

    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_2D, id);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_SRGB, GLint(png.width()), GLint(png.height()), 0, GL_RGBA, GL_UNSIGNED_BYTE, png.data());
    glGenerateMipmap(GL_TEXTURE_2D);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);

    loaded = true;
}

Texture::~Texture()
{
    destroy();
}

void Texture::bind(GLuint textureUnit)
{
    if (loaded) {
        glActiveTexture(textureUnit);
        glBindTexture(GL_TEXTURE_2D, id);
    } else {
        glActiveTexture(textureUnit);
        glBindTexture(GL_TEXTURE_2D, 0);
    }
}

void Texture::destroy()
{
    if (id) {
        glDeleteTextures(1, &id);
        loaded = false;
    }
}
