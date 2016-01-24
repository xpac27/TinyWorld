#include "MeshVertexArray.hpp"
#include "../utils/log.hpp"
#include <algorithm>

using namespace glm;
using namespace std;

void MeshVertexArray::initialize(std::vector<glm::vec4> &vertexes, std::vector<glm::vec2> &uvs, std::vector<glm::vec3> &normals, std::vector<glm::vec3> &tangents, std::vector<glm::vec3> &bitangents)
{
    std::vector<vec4> vertexesCopy;
    vertexesCopy.resize(vertexes.size());
    transform(vertexes.begin(), vertexes.end(), vertexesCopy.begin(), [](vec4 v) { v[3] = 0.f; return v; });

    glGenBuffers(7, VAB);
    glGenVertexArrays(1, &VAO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VAB[VER_VB]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 4 * vertexes.size() * 2, vertexes.data(), GL_STATIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 4 * vertexesCopy.size(), sizeof(GLfloat) * 4 * vertexesCopy.size(), vertexesCopy.data());
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, VAB[TEX_VB]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 2 * uvs.size(), uvs.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, VAB[NOR_VB]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 3 * normals.size(), normals.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER, VAB[TEN_VB]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 3 * tangents.size(), tangents.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(3);

    glBindBuffer(GL_ARRAY_BUFFER, VAB[BIT_VB]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 3 * bitangents.size(), bitangents.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(4);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VAB[IND_VB]);

    glBindBuffer(GL_ARRAY_BUFFER, VAB[WVP_VB]);
    for (unsigned int i = 0; i < 4 ; i++) {
        glVertexAttribPointer(5 + i, 4, GL_FLOAT, GL_FALSE, sizeof(mat4), reinterpret_cast<const GLvoid *>(sizeof(GLfloat) * i * 4));
        glVertexAttribDivisor(5 + i, 1);
        glEnableVertexAttribArray(5 + i);
    }

    glBindVertexArray(0);
}

void MeshVertexArray::uploadMatrices(unsigned int instances, const glm::mat4* matrices)
{
    glBindBuffer(GL_ARRAY_BUFFER, VAB[WVP_VB]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(mat4) * instances, matrices, GL_DYNAMIC_DRAW);
}

void MeshVertexArray::uploadIndexes(vector<unsigned int> &indexes)
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VAB[IND_VB]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indexes[0]) * indexes.size(), indexes.data(), GL_DYNAMIC_DRAW);
}

void MeshVertexArray::bind()
{
    glBindVertexArray(VAO);
}

void MeshVertexArray::idle()
{
    glBindVertexArray(0);
}
