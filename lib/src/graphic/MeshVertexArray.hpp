#pragma once
#include <GL/glew.h>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <vector>

#define VOL_VO 0
#define SIL_VO 1
#define SIL_VB 0
#define IND_VB 1
#define VER_VB 2
#define NOR_VB 3
#define TEX_VB 4
#define WVP_VB 5
#define W_VB 6

class MeshVertexArray
{
public:

    void initialize(std::vector<glm::vec3> &vertexes, std::vector<glm::vec2> &uvs, std::vector<glm::vec3> &normals, std::vector<unsigned int> &indexes);
    void uploadMatrices(unsigned int instances, const glm::mat4* WVPs, const glm::mat4* Ws);
    void uploadSilhouette(std::vector<unsigned int> &indexes);
    void bindVolume();
    void bindSilhouette();
    void idle();

private:

    GLuint VAO[2];
    GLuint VAB[7];
};
