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
    for (auto diffuse : diffuses) {
        glDeleteTextures(1, &diffuse);
    }
    delete vertexArray;
}

void Mesh::debug()
{
    OBJ::debug(triangles, vertexes, uvs, normals, indexes, materials);
}

void Mesh::bindTexture()
{
    if (diffuses.size() > 0) {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, diffuses[0]);
    }
}

void Mesh::updateShadowVolume(vec3 &lightDirection)
{
    updateTrianglesVisibility(lightDirection);
    updateSilhouette();
    // for (auto i : silouhette) {
    //     print("_", i);
    // }
    // printl("===============");
}

void Mesh::updateMatrices(unsigned int instances, const mat4* WVPs, const mat4* Ws)
{
    vertexArray->uploadMatrices(instances, WVPs, Ws);
}

void Mesh::draw(unsigned int instances)
{
    vertexArray->uploadIndexes(indexes);
    vertexArray->bind();
    glDrawElementsInstanced(GL_TRIANGLES, GLsizei(indexes.size()), GL_UNSIGNED_INT, 0, instances);
    vertexArray->idle();
}

void Mesh::drawShadowVolume(unsigned int instances)
{
    vertexArray->uploadIndexes(silouhette);
    vertexArray->bind();
    glDrawElementsInstanced(GL_LINES, GLsizei(silouhette.size()), GL_UNSIGNED_INT, 0, instances);
    vertexArray->idle();
}

void Mesh::loadTextures()
{
    for (auto &m : materials) {
        diffuses.push_back(loadTexture(m.map_Kd.data()));
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
        const vec3& v1 = vertexes[triangle[0]];
        const vec3& v2 = vertexes[triangle[1]];
        const vec3& v3 = vertexes[triangle[2]];
        // printl("v1", v1.x, v1.y, v1.z);
        // printl("v2", v2.x, v2.y, v2.z);
        // printl("v3", v3.x, v3.y, v3.z);
        //
        // printl(v1.y * (v2.z - v3.z) + v2.y * (v3.z - v1.z) + v3.y * (v1.z - v2.z));
        // printl(v1.z * (v2.x - v3.x) + v2.z * (v3.x - v1.x) + v3.z * (v1.x - v2.x));
        // printl(v1.x * (v2.y - v3.y) + v2.x * (v3.y - v1.y) + v3.x * (v1.y - v2.y));
        // printl(- (v1.x * (v2.y * v3.z - v3.y * v2.z) + v2.x * (v3.y * v1.z - v1.y * v3.z) + v3.x * (v1.y * v2.z - v2.y * v1.z)));

        trianglesPlaneEquations.push_back(vec4(
            v1.y * (v2.z - v3.z) + v2.y * (v3.z - v1.z) + v3.y * (v1.z - v2.z),
            v1.z * (v2.x - v3.x) + v2.z * (v3.x - v1.x) + v3.z * (v1.x - v2.x),
            v1.x * (v2.y - v3.y) + v2.x * (v3.y - v1.y) + v3.x * (v1.y - v2.y),
            - (v1.x * (v2.y * v3.z - v3.y * v2.z) + v2.x * (v3.y * v1.z - v1.y * v3.z) + v3.x * (v1.y * v2.z - v2.y * v1.z))
        ));
    }
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

void Mesh::updateTrianglesVisibility(vec3 &lightDirection)
{
    // printl("visibility:");
    // print("    ");
    for (unsigned int t = 0; t < triangles.size(); t ++) {
        trianglesVisibility[t] = (
            trianglesPlaneEquations[t][0] * lightDirection[0]
          + trianglesPlaneEquations[t][1] * lightDirection[1]
          + trianglesPlaneEquations[t][2] * lightDirection[2]
          + trianglesPlaneEquations[t][3] > 0);
        // printl(trianglesPlaneEquations[t][0], trianglesPlaneEquations[t][1], trianglesPlaneEquations[t][2], trianglesPlaneEquations[t][3]);
        // print(".", trianglesVisibility[t]);
    }
    // nl();
}

void Mesh::updateSilhouette()
{
    silouhette.clear();
    for (unsigned int t = 0; t < triangles.size(); t ++) {
        if (trianglesVisibility[t]) {
            // silouhette.push_back(triangles[t][0]);
            // silouhette.push_back(triangles[t][1]);
            // silouhette.push_back(triangles[t][1]);
            // silouhette.push_back(triangles[t][2]);
            // silouhette.push_back(triangles[t][2]);
            // silouhette.push_back(triangles[t][0]);

            for (int edge = 0; edge < 3; edge ++){ // For each visible triangle's edges
                // If edge's neighbouring face is not visible, or if it has no neighbour
                // then this edge's vertexes are part of the silouhette
                int neighbourIndex = trianglesNeighbours[t][edge];
                if (neighbourIndex == -1 || trianglesVisibility[unsigned(neighbourIndex)] == false) {
                    // print("Hop!");
                    silouhette.push_back(triangles[t][edge]);
                    silouhette.push_back(triangles[t][(edge + 1) % 3]);
                    // break;
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
