#pragma once
#include <SFML/OpenGL.hpp>
#include <SFML/Graphics.hpp>
#include "math/Vertex.hpp"
#include "math/Triangle.hpp"

class Mesh
{

public:

    Mesh();

    void draw();

private:

    unsigned int totalIndexes();
    unsigned int totalVertexes();

    GLuint VBOIds[2];

    Triangle triangles[2];
    Vertex vertexes[4];
    GLubyte indexes[6];
};

