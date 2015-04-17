#pragma once
#include <SFML/OpenGL.hpp>
#include <vector>
#include "graphic/Vertex.hpp"
#include "graphic/Normal.hpp"

class Mesh
{

public:

    Mesh(const char *filename);

    void draw();

private:

    GLuint VBOIds[2];
    GLsizei totalIndexes {0};

    std::vector<Vertex> vertexes;
    std::vector<Normal> normals;
    std::vector<GLubyte> indexes;
};

