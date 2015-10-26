#pragma once
#include <GL/glew.h>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/mat4x3.hpp>
#include <vector>

struct Material;
class MeshVertexArray;

class Mesh
{

public:

    Mesh(const char *filename);
    ~Mesh();

    void draw(unsigned int instances, const glm::mat4* WVPs, const glm::mat4* Ws);
    void updateShadowVolume(glm::vec3 &lightDirection, std::vector<glm::mat4x3> &quads, unsigned int &totalQuads);
    void bindTexture();
    void debug();

private:

    void loadVAO();
    void loadTextures();
    void verifyUVs();
    void verifyMeterials();
    void initializeTriangleData();
    void computeTrianglesPlaneEquations();
    void computeTrianglesNeighbours();
    void computeTrianglesVisibility(glm::vec3 &lightDirection);

    glm::mat4x3 extractQuadFromEdge(glm::vec3 &vertex1, glm::vec3 &vertex2, glm::vec3 &direction);

    GLuint loadTexture(const char *filename);

    MeshVertexArray* vertexArray;

    std::vector<unsigned int> indexes;
    std::vector<bool> trianglesVisibility;
    std::vector<glm::ivec3> trianglesNeighbours;
    std::vector<glm::vec4> trianglesPlaneEquations;
    std::vector<glm::uvec3> triangles;
    std::vector<glm::vec3> vertexes;
    std::vector<glm::vec2> uvs;
    std::vector<glm::vec3> normals;
    std::vector<Material> materials;
    std::vector<GLuint> diffuses;
};

