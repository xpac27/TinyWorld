#pragma once
#include <GL/glew.h>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <vector>

#define IND_VB 0
#define POS_VB 1
#define NOR_VB 2
#define TEX_VB 3
#define WVP_VB 4
#define W_VB 5

struct Material;

// struct Plane
// {
//     float a;
//     float b;
//     float c;
//     float d;
// };
//
// struct Triangle
// {
//     int vertexes[3];      // Index Of Each Vertex Within An Object That Makes Up The Triangle Of This Face
//     int neighbours[3];    // Index Of Each Triangle That Neighbours This One Within The Object
//     Plane equation;       // Equation Of A Plane That Contains This Triangle
//     bool visible;         // Is The Face Visible By The Light?
// };

class Mesh
{

public:

    Mesh(const char *filename);
    ~Mesh();

    void draw(unsigned int instances, const glm::mat4* WVPs, const glm::mat4* Ws);
    void bindTexture();
    void debug();

private:

    void loadVAO();
    void loadTextures();

    GLuint loadTexture(const char *filename);

    // TODO wrap that in a class
    GLuint VAO;
    GLuint VAB[6];
    GLsizei totalIndexes {0};

    std::vector<unsigned int> indexes;
    std::vector<glm::vec3> triangles;
    std::vector<glm::vec3> vertexes;
    std::vector<glm::vec2> uvs;
    std::vector<glm::vec3> normals;
    std::vector<Material> materials;
    std::vector<GLuint> diffuses;
};

