#pragma once
#include <graphic/MeshParams.hpp>
#include <OpenGL.hpp>
#include <glm/glm.hpp>

#include <vector>

class MeshVertexArray;
class Texture;

class Mesh
{
public:
    Mesh(MeshParams params);
    ~Mesh();

    void updateMatrices(unsigned int instances, const glm::mat4* matrices);
    void draw(unsigned int instances);
    void bindTexture(GLuint diffuse, GLuint metallic, GLuint rough, GLuint normal);
    void debug();

    #ifdef PLATFORM_OSX
    void drawAdjacency(unsigned int instances);
    #endif

private:

    void verifyUVs();
    void initializeTriangleData();
    void computeTrianglesPlaneEquations();
    void computeTrianglesTangents();

    MeshVertexArray* vertexArray;

    std::vector<unsigned int> indexes;
    std::vector<unsigned int> adjacencyIndexes;
    std::vector<glm::fvec3> trianglesTangents;
    std::vector<glm::fvec3> trianglesBitangents;
    std::vector<glm::fvec4> trianglesPlaneEquations;
    std::vector<glm::uvec3> triangles;
    std::vector<glm::vec4> vertexes;
    std::vector<glm::vec2> uvs;
    std::vector<glm::vec3> normals;

    Texture *diffuseTexture;
    Texture *metallicTexture;
    Texture *roughTexture;
    Texture *normalTexture;
};

