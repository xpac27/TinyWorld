#pragma once
#include "graphic/Vertex.hpp"
#include "graphic/Normal.hpp"
#include <GL/glew.h>
#include <vector>

class Mesh
{

public:

    Mesh(const char *filename);

    void draw();
    void outline();

private:

    void loadVBOs();

    GLuint VBOIds[2];
    GLsizei totalIndexes {0};

    std::vector<Vertex> vertexes;
    std::vector<Normal> normals;
    std::vector<GLubyte> indexes;
};

