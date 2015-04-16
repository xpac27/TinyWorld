#include "Mesh.hpp"
#include "helpers/Debug.hpp"
#include "utils/OBJLoader.hpp"

using namespace std;

Mesh::Mesh(const char *filename)
{
    OBJLoader::loadOBJ(vertexes, normals, indexes, filename);

    totalIndexes = GLsizei(indexes.size());
    // Debug::printl(totalIndexes);
    Debug::printl(vertexes.size());
    Debug::printl(sizeof(Vertex));
    Debug::printl(sizeof(Vertex) * vertexes.size());
    Debug::printl(sizeof(*vertexes.data()));
    Debug::printl(vertexes.data());
    Debug::printl(indexes.data());

    glGenBuffers(2, VBOIds);

    glBindBuffer(GL_ARRAY_BUFFER, VBOIds[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * unsigned(vertexes.size()), vertexes.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VBOIds[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * unsigned(indexes.size()), indexes.data(), GL_STATIC_DRAW);
}

void Mesh::draw()
{
    Debug::printl(vertexes.data());
    Debug::printl(indexes.data());
    glBindBuffer(GL_ARRAY_BUFFER, VBOIds[0]);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VBOIds[1]);
    glDrawElements(GL_TRIANGLES, totalIndexes, GL_UNSIGNED_BYTE, NULL);
}
