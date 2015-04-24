#include "Mesh.hpp"
#include "utils/OBJLoader.hpp"
#include "helpers/Debug.hpp"

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
        vertexes[i].col[3] = 1.f;
    }

    loadVBOs();
}

void Mesh::debug()
{
    OBJLoader::debug(vertexes, normals, indexes);
}

void Mesh::loadVBOs()
{
    if (GLEW_ARB_vertex_buffer_object)
    {
        glGenBuffers(2, VBOIds);

        glBindBuffer(GL_ARRAY_BUFFER, VBOIds[0]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * unsigned(vertexes.size()), vertexes.data(), GL_STATIC_DRAW);
        // glBufferSubData TODO

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VBOIds[1]);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * unsigned(indexes.size()), indexes.data(), GL_STATIC_DRAW);
        // glBufferSubData TODO
    }
}

void Mesh::draw()
{
    if (GLEW_ARB_vertex_buffer_object)
    {
        glBindBuffer(GL_ARRAY_BUFFER, VBOIds[0]);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VBOIds[1]);
        glDrawElements(GL_TRIANGLES, totalIndexes, GL_UNSIGNED_INT, NULL);
    }
}

void Mesh::outline()
{
    if (GLEW_ARB_vertex_buffer_object)
    {
        glBindBuffer(GL_ARRAY_BUFFER, VBOIds[0]);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VBOIds[1]);
        glDrawElements(GL_LINE_LOOP, totalIndexes, GL_UNSIGNED_BYTE, NULL);
    }
}
