#include "Cubemap.hpp"
#include "PNG.hpp"
#include <string>

using namespace std;

void Cubemap::load(const vector<const char*> filenames)
{
    if (loaded) destroy();

    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_CUBE_MAP, id);
    for(GLuint i = 0; i < filenames.size(); i++) {
        string filepath = "lib/res/";
        filepath += filenames[i];
        PNG png(filepath.data());
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, GLint(png.width()), GLint(png.height()), 0, GL_RGBA, GL_UNSIGNED_BYTE, png.data());
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

    loaded = true;
}

Cubemap::~Cubemap()
{
    destroy();
}

void Cubemap::bind(GLuint textureUnit)
{
    if (loaded) {
        glActiveTexture(textureUnit);
        glBindTexture(GL_TEXTURE_CUBE_MAP, id);
    }
}

void Cubemap::destroy()
{
    if (id) {
        glDeleteTextures(1, &id);
    }
}
