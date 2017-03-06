#pragma once
#include "OpenGL.hpp"
#include "GLM.hpp"
#include <vector>

#define IND_VB 0
#define VER_VB 1
#define NOR_VB 2
#define TEX_VB 3
#define TEN_VB 4
#define BIT_VB 5
#define WVP_VB 6

class MeshVertexArray
{
public:

    void initialize(std::vector<glm::vec4> &vertexes, std::vector<glm::vec2> &uvs, std::vector<glm::vec3> &normals, std::vector<glm::vec3> &tangents, std::vector<glm::vec3> &bitangents);
    void uploadMatrices(unsigned int instances, const glm::mat4* matrices);
    void uploadIndexes(std::vector<unsigned int> &indexes);
    void bind();
    void idle();

private:

    GLuint VAO;
    GLuint VAB[7];
};
