#include "Mesh.hpp"
#include "graphic/Material.hpp"
#include "graphic/MeshVertexArray.hpp"
#include "utils/OBJ.hpp"
#include "utils/PNG.hpp"
#include "utils/Log.hpp"
#include <string>

using namespace std;
using namespace glm;
using namespace Log;

Mesh::Mesh(const char *filename)
    : vertexArray(new MeshVertexArray())
{
    OBJ(triangles, vertexes, uvs, normals, indexes, materials).load(filename);

    verifyUVs();
    verifyMeterials();
    vertexArray->initialize(vertexes, uvs, normals);
    loadTextures();
    initializeTriangleData();
    computeTrianglesPlaneEquations();
    computeTrianglesNeighbours();
}

Mesh::~Mesh()
{
    for (auto diffuseTexture : diffuseTextures) {
        glDeleteTextures(1, &diffuseTexture);
    }
    for (auto specularTexture : specularTextures) {
        glDeleteTextures(1, &specularTexture);
    }
    for (auto normalTexture : normalTextures) {
        glDeleteTextures(1, &normalTexture);
    }
    delete vertexArray;
}

void Mesh::debug()
{
    OBJ::debug(triangles, vertexes, uvs, normals, indexes, materials);
}

void Mesh::bindTexture()
{
    if (diffuseTextures.size() > 0) {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, diffuseTextures[0]);
    }
    if (specularTextures.size() > 0) {
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, specularTextures[0]);
    }
    if (normalTextures.size() > 0) {
        glActiveTexture(GL_TEXTURE2);
        glBindTexture(GL_TEXTURE_2D, normalTextures[0]);
    }
}

void Mesh::bindIndexes()
{
    vertexArray->uploadIndexes(indexes);
}

void Mesh::bindSilhouette()
{
    vertexArray->uploadIndexes(silhouette);
}

void Mesh::updateShadowVolume(const vec4 &lightDirection)
{
    updateTrianglesVisibility(lightDirection);
    updateSilhouette();
}

void Mesh::updateMatrices(unsigned int instances, const mat4* matrices)
{
    vertexArray->uploadMatrices(instances, matrices);
}

void Mesh::draw(unsigned int instances)
{
    vertexArray->bind();
    glDrawElementsInstanced(GL_TRIANGLES, GLsizei(indexes.size()), GL_UNSIGNED_INT, 0, instances);
    vertexArray->idle();
}

void Mesh::drawShadowVolume()
{
    if (silhouette.size() == 0) return;

    vertexArray->bind();
    glDrawElements(GL_TRIANGLES, GLsizei(silhouette.size()), GL_UNSIGNED_INT, 0);
    vertexArray->idle();
}

void Mesh::loadTextures()
{
    for (auto &m : materials) {
        diffuseTextures.push_back(loadTexture(m.map_Kd.data()));
        specularTextures.push_back(loadTexture(m.map_Ks.data()));
        normalTextures.push_back(loadTexture(m.map_Bump.data()));
    }
}

void Mesh::verifyUVs()
{
    if (uvs.size() < vertexes.size()) {
        uvs.resize(vertexes.size(), vec2(0.f));
    }
}

void Mesh::verifyMeterials()
{
    if (materials.size() == 0) {
        materials.push_back(Material("default"));
    }
}

void Mesh::initializeTriangleData()
{
    trianglesVisibility.resize(triangles.size(), false);
    trianglesNeighbours.resize(triangles.size(), ivec3(-1, -1, -1));
    trianglesPlaneEquations.reserve(triangles.size());
}

void Mesh::computeTrianglesPlaneEquations()
{
    for (auto &triangle : triangles) {
        const vec4& v1 = vertexes[triangle[0]];
        const vec4& v2 = vertexes[triangle[1]];
        const vec4& v3 = vertexes[triangle[2]];

        trianglesPlaneEquations.push_back(fvec4(
              v1.y * (v2.z - v3.z)
            + v2.y * (v3.z - v1.z)
            + v3.y * (v1.z - v2.z),

              v1.z * (v2.x - v3.x)
            + v2.z * (v3.x - v1.x)
            + v3.z * (v1.x - v2.x),

              v1.x * (v2.y - v3.y)
            + v2.x * (v3.y - v1.y)
            + v3.x * (v1.y - v2.y),

            -(v1.x * (v2.y * v3.z - v3.y * v2.z)
            + v2.x * (v3.y * v1.z - v1.y * v3.z)
            + v3.x * (v1.y * v2.z - v2.y * v1.z))
        ));
    }
    // for (auto &e : trianglesPlaneEquations) {
    //     printl(e.x, e.y, e.z, e.w);
    // }
}

void Mesh::computeTrianglesNeighbours()
{
    for (unsigned int t1 = 0; t1 < triangles.size(); t1++) {
        for (unsigned int t2 = t1 + 1; t2 < triangles.size(); t2++) {
            for (int a = 0; a < 3; a++) {
                if (trianglesNeighbours[t1][a] == -1) {
                    for (int b = 0; b < 3; b++) {
                        unsigned int triangle_1_indexA = triangles[t1][a];
                        unsigned int triangle_1_indexB = triangles[t1][(a + 1) % 3];
                        unsigned int triangle_2_indexA = triangles[t2][b];
                        unsigned int triangle_2_indexB = triangles[t2][(b + 1) % 3];

                        if ((triangle_1_indexA == triangle_2_indexA && triangle_1_indexB == triangle_2_indexB)
                        || (triangle_1_indexA == triangle_2_indexB && triangle_1_indexB == triangle_2_indexA)) {
                            trianglesNeighbours[t1][a] = int(t2);
                            trianglesNeighbours[t2][b] = int(t1);
                            break;
                        }
                    }
                }
            }
        }
    }
}

void Mesh::updateTrianglesVisibility(const vec4 &lightDirection)
{
	// TODO optimize
    for (unsigned int t = 0; t < triangles.size(); t ++) {
        trianglesVisibility[t] = dot(trianglesPlaneEquations[t], lightDirection) > 0.f;
    }
}

void Mesh::updateSilhouette()
{
	// TODO optimize
    silhouette.clear();
    unsigned int totalVertexes = unsigned(vertexes.size());
    for (unsigned int t = 0; t < triangles.size(); t ++) {
        if (trianglesVisibility[t]) {
            for (int edge = 0; edge < 3; edge ++){ // For each visible triangle's edges
                // If edge's neighbouring face is not visible, or if it has no neighbour
                // then this edge's vertexes are part of the silhouette
                int neighbourIndex = trianglesNeighbours[t][edge];
                if (neighbourIndex == -1 || trianglesVisibility[unsigned(neighbourIndex)] == false) {
                    silhouette.push_back(triangles[t][(edge + 1) % 3]);
                    silhouette.push_back(triangles[t][edge] + totalVertexes);
                    silhouette.push_back(triangles[t][edge]);
                }
            }
        }
    }
}

GLuint Mesh::loadTexture(const char *filename)
{
    string filepath = "app/res/";
    filepath += filename;
    PNG png(filepath.data());

    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, GLint(png.width()), GLint(png.height()), 0, GL_RGBA, GL_UNSIGNED_BYTE, png.data());
    glGenerateMipmap(GL_TEXTURE_2D);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);

    return texture;
}
