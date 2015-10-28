#pragma once
#include <GL/glew.h>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <vector>

#define IND_VB 0
#define VER_VB 1
#define NOR_VB 2
#define TEX_VB 3
#define WVP_VB 4
#define W_VB 5

class MeshVertexArray
{
public:

    void initialize(std::vector<glm::vec3> &vertexes, std::vector<glm::vec2> &uvs, std::vector<glm::vec3> &normals);
    void uploadMatrices(unsigned int instances, const glm::mat4* WVPs, const glm::mat4* Ws);
    void uploadIndexes(std::vector<unsigned int> &indexes);
    void bind();
    void idle();

private:

    GLuint VAO;
    GLuint VAB[6];
};
