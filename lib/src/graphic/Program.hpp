#pragma once
#include <GL/glew.h>

class Program
{

public:

    // TODO pass file objects instead of file paths
    Program(const char* vertexShaderFilePath, const char* fragmentShaderFilePath);
    Program(const char* vertexShaderFilePath, const char* geometryShaderFilePath, const char* fragmentShaderFilePath);

    ~Program();

    void use() const;
    void idle() const;

    GLint getLocation(const char* variable) const;

private:

    Program();

    void link() const;

    GLuint reference;

};
