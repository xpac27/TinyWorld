#include "Mesh.hpp"
#include "utils/OBJLoader.hpp"
#include "helpers/Debug.hpp"

using namespace std;

Mesh::Mesh(const char *filename)
{
    OBJLoader().load(vertexes, normals, indexes, filename);
    totalIndexes = GLsizei(indexes.size());

    loadVAO();
}

void Mesh::debug()
{
    OBJLoader().debug(vertexes, normals, indexes);
}

void Mesh::loadVAO()
{
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(4, VAB);

    glBindBuffer(GL_ARRAY_BUFFER, VAB[POS_VB]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexes[0]) * vertexes.size(), vertexes.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, VAB[NOR_VB]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(normals[0]) * normals.size(), normals.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VAB[IND_VB]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indexes[0]) * indexes.size(), indexes.data(), GL_STATIC_DRAW);

    glBindVertexArray(0);
}

void Mesh::draw()
{
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, totalIndexes, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void Mesh::outline()
{
    glBindVertexArray(VAO);
    glDrawElements(GL_LINE_LOOP, totalIndexes, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}
