#pragma once
#include <GL/glew.h>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/glm.hpp>
#include <vector>

struct Material;
class MeshVertexArray;
class Texture;

class Mesh
{

public:

    Mesh(const char *filename);
    ~Mesh();

    void updateShadowVolume(const glm::vec4 &lightDirection);
    void updateMatrices(unsigned int instances, const glm::mat4* matrices);
    void draw(unsigned int instances);
    void drawShadowVolume();
    void reloadTextures();
    void bindTexture(GLuint diffuse, GLuint metallic, GLuint rough, GLuint normal);
    void bindIndexes();
    void bindSilhouette();
    void debug();

private:

    void loadTextures();
    void verifyUVs();
    void verifyMeterials();
    void initializeTriangleData();
    void computeTrianglesPlaneEquations();
    void computeTrianglesTangents();
    void computeTrianglesNeighbours();
    void updateTrianglesVisibility(const glm::vec4 &lightDirection);
    void updateSilhouette();

    MeshVertexArray* vertexArray;

    std::vector<unsigned int> indexes;
    std::vector<unsigned int> silhouette;
    std::vector<bool> trianglesVisibility;
    std::vector<glm::ivec3> trianglesNeighbours;
    std::vector<glm::fvec3> trianglesTangents;
    std::vector<glm::fvec3> trianglesBitangents;
    std::vector<glm::fvec4> trianglesPlaneEquations;
    std::vector<glm::uvec3> triangles;
    std::vector<glm::vec4> vertexes;
    std::vector<glm::vec2> uvs;
    std::vector<glm::vec3> normals;
    std::vector<Material> materials;

    Texture *diffuseTexture;
    Texture *metallicTexture;
    Texture *roughTexture;
    Texture *normalTexture;
};

