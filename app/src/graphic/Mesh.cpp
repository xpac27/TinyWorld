#include "Mesh.hpp"
#include "utils/OBJLoader.hpp"
#include "helpers/Debug.hpp"

using namespace std;

Mesh::Mesh(const char *filename)
{
    OBJLoader::loadOBJ(vertexes, normals, indexes, filename);
    totalIndexes = GLsizei(indexes.size());

    // loadVAO();
}

void Mesh::debug()
{
    OBJLoader::debug(vertexes, normals, indexes);
}

void Mesh::loadVAO()
{
    if (GLEW_ARB_vertex_array_object && GLEW_ARB_vertex_buffer_object)
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

        glBindBuffer(GL_ARRAY_BUFFER, VAB[IND_VB]);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indexes[0]) * indexes.size(), indexes.data(), GL_STATIC_DRAW);

        glBindVertexArray(0);
    }
}

void Mesh::draw()
{
    glBegin(GL_TRIANGLES);
    glColor4f(1.f, 1.f, 0.f, 1.f);
    for (auto i : indexes) {
        glVertex3f(vertexes[i].x, vertexes[i].y, vertexes[i].z);
        glNormal3f(normals[i].x, normals[i].y, normals[i].z);
    }
    glEnd();

    // if (GLEW_ARB_vertex_array_object && GLEW_ARB_vertex_buffer_object)
    // {
    //     glColor4f(1.f, 1.f, 0.f, 1.f);
    //     glBindVertexArray(VAO);
    //     glDrawArrays(GL_TRIANGLES, 0, totalIndexes);
    //     // glDrawElements(GL_TRIANGLES, totalIndexes, GL_UNSIGNED_INT, indexes.data());
    //     // glDrawElementsBaseVertex(GL_TRIANGLES, totalIndexes, GL_UNSIGNED_INT, indexes.data(), vertexes.size());
    //     glBindVertexArray(0);
    // }
}

void Mesh::outline()
{
    if (GLEW_ARB_vertex_array_object && GLEW_ARB_vertex_buffer_object)
    {
        // glColor4f(1.f, 1.f, 1.f, 1.f);
        // glBindVertexArray(VAO);
        // glDrawElements(GL_LINE_LOOP, totalIndexes, GL_UNSIGNED_BYTE, NULL);
        // glBindVertexArray(0);
    }
}
