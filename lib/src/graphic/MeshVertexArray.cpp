#include "MeshVertexArray.hpp"

using namespace glm;

void MeshVertexArray::initialize(std::vector<glm::vec3> &vertexes, std::vector<glm::vec2> &uvs, std::vector<glm::vec3> &normals, std::vector<unsigned int> &indexes)
{
    glGenBuffers(7, VAB);
    glGenVertexArrays(2, VAO);

    glBindVertexArray(VAO[VOL_VO]);

    glBindBuffer(GL_ARRAY_BUFFER, VAB[VER_VB]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 3 * vertexes.size(), vertexes.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, VAB[TEX_VB]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 2 * uvs.size(), uvs.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, VAB[NOR_VB]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 3 * normals.size(), normals.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VAB[IND_VB]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indexes[0]) * indexes.size(), indexes.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, VAB[WVP_VB]);
    for (unsigned int i = 0; i < 4 ; i++) {
        glVertexAttribPointer(3 + i, 4, GL_FLOAT, GL_FALSE, sizeof(mat4), reinterpret_cast<const GLvoid *>(sizeof(GLfloat) * i * 4));
        glVertexAttribDivisor(3 + i, 1);
        glEnableVertexAttribArray(3 + i);
    }

    glBindBuffer(GL_ARRAY_BUFFER, VAB[W_VB]);
    for (unsigned int i = 0; i < 4 ; i++) {
        glVertexAttribPointer(7 + i, 4, GL_FLOAT, GL_FALSE, sizeof(mat4), reinterpret_cast<const GLvoid *>(sizeof(GLfloat) * i * 4));
        glVertexAttribDivisor(7 + i, 1);
        glEnableVertexAttribArray(7 + i);
    }

    glBindVertexArray(VAO[SIL_VO]);
    glBindBuffer(GL_ARRAY_BUFFER, VAB[VER_VB]);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VAB[SIL_VB]);

    glBindVertexArray(0);
}

void MeshVertexArray::uploadMatrices(unsigned int instances, const glm::mat4* WVPs, const glm::mat4* Ws)
{
    glBindBuffer(GL_ARRAY_BUFFER, VAB[WVP_VB]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(mat4) * instances, WVPs, GL_DYNAMIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, VAB[W_VB]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(mat4) * instances, Ws, GL_DYNAMIC_DRAW);
}

void MeshVertexArray::uploadSilhouette(std::vector<unsigned int> &indexes)
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VAB[SIL_VB]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indexes[0]) * indexes.size(), indexes.data(), GL_DYNAMIC_DRAW);
}

void MeshVertexArray::bindVolume()
{
    glBindVertexArray(VAO[VOL_VO]);
}

void MeshVertexArray::bindSilhouette()
{
    glBindVertexArray(VAO[SIL_VO]);
}

void MeshVertexArray::idle()
{
    glBindVertexArray(0);
}
