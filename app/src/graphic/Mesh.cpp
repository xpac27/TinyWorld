#include "Mesh.hpp"
#include "helpers/Debug.hpp"
#include "math/Vertex.hpp"
#include "tiny_obj_loader.h"
#include <vector>

using namespace std;
using namespace tinyobj;

Mesh::Mesh(std::string objFilePath)
{
    vector<shape_t> shapes;
    vector<material_t> materials;
    string error = LoadObj(shapes, materials, objFilePath.c_str());

    if (!error.empty() || shapes.size() == 0) {
        Debug::printl("ERROR - could not load:", objFilePath);
        return;
    }

    Debug::printl(shapes[0].mesh.positions.size());
    vector<Vertex> vertexes;
    for (unsigned i = 0; i < shapes[0].mesh.positions.size(); i += 3) {
        vertexes.push_back(Vertex());
        vertexes.back().pos[0] = shapes[0].mesh.positions[i + 0];
        vertexes.back().pos[1] = shapes[0].mesh.positions[i + 1];
        vertexes.back().pos[2] = shapes[0].mesh.positions[i + 2];
    }

    vector<GLubyte> indexes;
    for (unsigned i = 0; i < shapes[0].mesh.indices.size(); i += 3) {
        indexes.push_back(GLubyte(shapes[0].mesh.indices[i]));
    }

    totalIndexes = GLsizei(indexes.size());
    Debug::printl(totalIndexes);

    glGenBuffers(2, VBOIds);

    glBindBuffer(GL_ARRAY_BUFFER, VBOIds[0]);
    glBufferData(GL_ARRAY_BUFFER, GLsizeiptr(sizeof(Vertex) * vertexes.size()), vertexes.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VBOIds[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, GLsizeiptr(sizeof(GLubyte) * indexes.size()), indexes.data(), GL_STATIC_DRAW);
}

void Mesh::draw()
{
    // glBindBuffer(GL_ARRAY_BUFFER, VBOIds[0]);
    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VBOIds[1]);
    // glDrawElements(GL_TRIANGLES, totalIndexes, GL_UNSIGNED_BYTE, NULL);
}
