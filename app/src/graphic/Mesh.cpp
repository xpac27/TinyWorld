#include "Mesh.hpp"

Mesh::Mesh()
{
    vertexes[0].pos[0] = -1.f;
    vertexes[0].pos[1] =  1.f;
    vertexes[0].pos[2] =  0.f;

    vertexes[1].pos[0] =  1.f;
    vertexes[1].pos[1] =  1.f;
    vertexes[1].pos[2] =  0.f;

    vertexes[2].pos[0] =  1.f;
    vertexes[2].pos[1] = -1.f;
    vertexes[2].pos[2] =  0.f;

    vertexes[3].pos[0] = -1.f;
    vertexes[3].pos[1] = -1.f;
    vertexes[3].pos[2] =  0.f;

    triangles[0].vi[0] = indexes[0] = 0;
    triangles[0].vi[1] = indexes[1] = 1;
    triangles[0].vi[2] = indexes[2] = 2;

    triangles[1].vi[0] = indexes[3] = 2;
    triangles[1].vi[1] = indexes[4] = 3;
    triangles[1].vi[2] = indexes[5] = 0;

    for (unsigned int i = 0; i < totalVertexes(); i++)
    {
        vertexes[i].col[0] = 1.0f;
        vertexes[i].col[1] = 1.0f;
        vertexes[i].col[2] = 0.0f;
        vertexes[i].col[3] = 0.2f;
    }

    glGenBuffers(2, VBOIds);

    glBindBuffer(GL_ARRAY_BUFFER, VBOIds[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * totalVertexes(), vertexes, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VBOIds[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLubyte) * totalIndexes(), indexes, GL_STATIC_DRAW);
}

void Mesh::draw()
{
    glBindBuffer(GL_ARRAY_BUFFER, VBOIds[0]);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VBOIds[1]);
    glDrawElements(GL_TRIANGLES, GLsizei(totalIndexes()), GL_UNSIGNED_BYTE, NULL);
}

unsigned int Mesh::totalIndexes()
{
    return sizeof(indexes) / sizeof(GLuint);
}

unsigned int Mesh::totalVertexes()
{
    return sizeof(vertexes) / sizeof(Vertex);
}
