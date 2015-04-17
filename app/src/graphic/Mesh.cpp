#include "Mesh.hpp"
#include "helpers/Debug.hpp"
#include "utils/OBJLoader.hpp"

#define BUFFER_OFFSET(i) ((char *)NULL + (i))

using namespace std;

Mesh::Mesh(const char *filename)
{
    OBJLoader::loadOBJ(vertexes, normals, indexes, filename);

    totalIndexes = GLsizei(indexes.size());

    for (unsigned int i = 0; i < vertexes.size(); i++)
    {
        vertexes[i].col[0] = 1.f;
        vertexes[i].col[1] = 1.f;
        vertexes[i].col[2] = 0.f;
        vertexes[i].col[3] = 0.2f;
    }

    glGenBuffers(2, VBOIds);

    glBindBuffer(GL_ARRAY_BUFFER, VBOIds[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * unsigned(vertexes.size()), vertexes.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VBOIds[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLubyte) * unsigned(indexes.size()), indexes.data(), GL_STATIC_DRAW);

    // Try to put that in the init of RenderSystem
    glVertexPointer(3, GL_FLOAT, sizeof(Vertex), BUFFER_OFFSET(0));
    glTexCoordPointer(2, GL_FLOAT, sizeof(Vertex), BUFFER_OFFSET(3));
    glNormalPointer(GL_FLOAT, sizeof(Vertex), BUFFER_OFFSET(5));
    glColorPointer(4, GL_FLOAT, sizeof(Vertex), BUFFER_OFFSET(8));
}

void Mesh::draw()
{
    glBindBuffer(GL_ARRAY_BUFFER, VBOIds[0]);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VBOIds[1]);
    glDrawElements(GL_TRIANGLES, totalIndexes, GL_UNSIGNED_BYTE, NULL);
}
