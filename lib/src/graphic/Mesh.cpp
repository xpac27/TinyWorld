#include "Mesh.hpp"
#include "graphic/Material.hpp"
#include "utils/OBJ.hpp"
#include "utils/PNG.hpp"
#include "utils/Log.hpp"
#include <string>

using namespace std;
using namespace glm;
using namespace Log;

Mesh::Mesh(const char *filename)
{
    OBJ(triangles, vertexes, uvs, normals, indexes, materials).load(filename);

    totalIndexes = GLsizei(indexes.size());

    verifyUVs();
    verifyMeterials();
    loadVAO();
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

void Mesh::draw(unsigned int instances, const glm::mat4* WVPs, const glm::mat4* Ws)
{
    if (instances == 0) return;

    glBindBuffer(GL_ARRAY_BUFFER, VAB[WVP_VB]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(mat4) * instances, WVPs, GL_DYNAMIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, VAB[W_VB]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(mat4) * instances, Ws, GL_DYNAMIC_DRAW);

    glBindVertexArray(VAO);

    glDrawElementsInstanced(GL_TRIANGLES, totalIndexes, GL_UNSIGNED_INT, 0, instances);

    glBindVertexArray(0);
}

void Mesh::loadVAO()
{
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(6, VAB);

    glBindBuffer(GL_ARRAY_BUFFER, VAB[POS_VB]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 3 * vertexes.size(), vertexes.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, VAB[TEX_VB]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 2 * uvs.size(), uvs.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, VAB[NOR_VB]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 3 * normals.size(), normals.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VAB[IND_VB]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indexes[0]) * indexes.size(), indexes.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, VAB[WVP_VB]);
    for (unsigned int i = 0; i < 4 ; i++) {
        glVertexAttribPointer(3 + i, 4, GL_FLOAT, GL_FALSE, sizeof(mat4), reinterpret_cast<const GLvoid *>(sizeof(GLfloat) * i * 4));
        glVertexAttribDivisor(3 + i, 1);
        glEnableVertexAttribArray(3 + i);
    }

    glBindBuffer(GL_ARRAY_BUFFER, VAB[W_VB]);
    for (unsigned int i = 0; i < 4 ; i++) {
        glVertexAttribPointer(7 + i, 4, GL_FLOAT, GL_FALSE, sizeof(mat4), reinterpret_cast<const GLvoid *>(sizeof(GLfloat) * i * 4));
        glVertexAttribDivisor(7 + i, 1);
        glEnableVertexAttribArray(7 + i);
    }

    glBindVertexArray(0);
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
    trianglesPlaneEquations.resize(triangles.size());
}

void Mesh::computeTrianglesPlaneEquations()
{
    for (auto &triangle : triangles) {
        const vec3& v1 = vertexes[triangle[0]];
        const vec3& v2 = vertexes[triangle[1]];
        const vec3& v3 = vertexes[triangle[2]];

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
                        unsigned int triangle_1_indexB = triangles[t1][b];
                        unsigned int triangle_2_indexA = triangles[t2][a];
                        unsigned int triangle_2_indexB = triangles[t2][b];

                        if ((triangle_1_indexA == triangle_2_indexA && triangle_1_indexB == triangle_2_indexB)
                        || (triangle_1_indexA == triangle_2_indexB && triangle_1_indexB == triangle_2_indexA)) {
                            trianglesNeighbours[t1][a] = int(t2);
                            trianglesNeighbours[t2][b] = int(t1);
                        }
                    }
                }
            }
        }
    }
}

void Mesh::computeTrianglesVisibility(glm::vec3 &lightDirection)
{
    for (unsigned int t = 0; t < triangles.size(); t ++) {
        trianglesVisibility[t] = (
            trianglesPlaneEquations[t][0] * lightDirection[0]
          + trianglesPlaneEquations[t][1] * lightDirection[1]
          + trianglesPlaneEquations[t][2] * lightDirection[2]
          + trianglesPlaneEquations[t][3] > 0);
    }
}

// TODO save shadow if light and mesh are linked to static entities
void Mesh::updateShadowVolume(vec3 &lightDirection, vector<mat4x3> &quads, unsigned int &totalQuads)
{
    computeTrianglesVisibility(lightDirection);

    totalQuads = 0;

    // For each visible triangle
    for (unsigned int t = 0; t < triangles.size(); t ++) {
        if (trianglesVisibility[t]) {

            // For each edge of the triangle
            for (int edge = 0; edge < 3; edge ++){

                // If edge's neighbouring face is not visible, or if there is no neighbour
                // then this edge is part of the silouhette
                int neighbourIndex = trianglesNeighbours[t][edge];
                if (neighbourIndex == -1 || trianglesVisibility[unsigned(neighbourIndex)] == false) {

                    // Get edge's vertexes
                    vec3& vertex1 = vertexes[triangles[t][edge]];
                    vec3& vertex2 = vertexes[triangles[t][(edge + 1) % 3]];

                    // Overwrite or push a new quad into the list
                    if (totalQuads < quads.size()) {
                        quads[totalQuads] = extractQuadFromEdge(vertex1, vertex2, lightDirection);
                    } else {
                        quads.push_back(extractQuadFromEdge(vertex1, vertex2, lightDirection));
                    }

                    ++totalQuads;
                }
            }
        }
    }
}

glm::mat4x3 Mesh::extractQuadFromEdge(glm::vec3 &vertex1, glm::vec3 &vertex2, glm::vec3 &direction)
{
    return mat4x3(vertex1, vertex2, vertex1 * direction * 1000.f, vertex2 * direction * 1000.f);
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
