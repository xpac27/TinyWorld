#pragma once
#include "graphic/Vertex.hpp"
#include "graphic/Normal.hpp"
#include <GL/glew.h>
#include <vector>

#define IND_VB 0
#define POS_VB 1
#define NOR_VB 2
#define COL_VB 3

class Mesh
{

public:

    Mesh(const char *filename);

    void draw();
    void debug();
    void outline();

private:

    void loadVAO();

    GLuint VAO;
    GLuint VAB[4];
    GLsizei totalIndexes {0};

    std::vector<Vertex> vertexes;
    std::vector<Normal> normals;
    std::vector<unsigned int> indexes;
};

