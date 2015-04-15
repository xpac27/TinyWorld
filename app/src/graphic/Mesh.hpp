#pragma once
#include <SFML/OpenGL.hpp>
#include <string>

class Mesh
{

public:

    Mesh(std::string objFilePath);

    void draw();

private:

    GLuint VBOIds[2];
    GLsizei totalIndexes {0};
};

