#pragma once
#include <GL/glew.h>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <vector>

#define IND_VB 0
#define POS_VB 1
#define NOR_VB 2
#define TEX_VB 3

struct Material;

class Mesh
{

public:

    Mesh(const char *filename);

    void draw();
    void debug();

private:

    void loadVAO();
    void loadTextures();
    GLuint loadTexture(const char *filename);

    GLuint VAO;
    GLuint VAB[4];
    GLsizei totalIndexes {0};

    std::vector<glm::vec3> vertexes;
    std::vector<glm::vec2> uvs;
    std::vector<glm::vec3> normals;
    std::vector<unsigned int> indexes;
    std::vector<Material> materials;
    std::vector<GLuint> diffuses;
};

