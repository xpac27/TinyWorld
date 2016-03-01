#include "Mesh.hpp"
#include "../../inc/utils/Utility.hpp"
#include "../utils/Texture.hpp"
#include "../utils/OBJ.hpp"
#include "../utils/log.hpp"
#include "../utils/Manifold.hpp"
#include "Material.hpp"
#include "MeshVertexArray.hpp"

using namespace std;
using namespace glm;

Mesh::Mesh(MeshParams params)
    : vertexArray(new MeshVertexArray())
    , diffuseTexture(new Texture())
    , metallicTexture(new Texture())
    , roughTexture(new Texture())
    , normalTexture(new Texture())
{
    OBJ(triangles, vertexes, uvs, normals, indexes).load(params.object);

    verifyUVs();

    initializeTriangleData(); // TODO Move to manifold
    computeTrianglesPlaneEquations(); // TODO Move to manifold
    computeTrianglesTangents(); // TODO Move to manifold
    generateTrianglesAdjacencyIndex(triangles, adjacencyIndexes);

    vertexArray->initialize(vertexes, uvs, normals, trianglesTangents, trianglesBitangents);

    if (!isEmpty(params.diffuseTexture)) diffuseTexture->load(params.diffuseTexture);
    if (!isEmpty(params.metallicTexture)) metallicTexture->load(params.metallicTexture);
    if (!isEmpty(params.roughTexture)) roughTexture->load(params.roughTexture);
    if (!isEmpty(params.normalTexture)) normalTexture->load(params.normalTexture);
}

Mesh::~Mesh()
{
    delete diffuseTexture;
    delete metallicTexture;
    delete roughTexture;
    delete normalTexture;
    delete vertexArray;
}

void Mesh::debug()
{
    OBJ::debug(triangles, vertexes, uvs, normals, indexes);
}

void Mesh::bindTexture(GLuint diffuse, GLuint metallic, GLuint rough, GLuint normal)
{
    diffuseTexture->bind(diffuse);
    metallicTexture->bind(metallic);
    roughTexture->bind(rough);
    normalTexture->bind(normal);
}

void Mesh::updateMatrices(unsigned int instances, const mat4* matrices)
{
    vertexArray->uploadMatrices(instances, matrices);
}

void Mesh::draw(unsigned int instances)
{
    vertexArray->uploadIndexes(indexes);
    vertexArray->bind();
    glDrawElementsInstanced(GL_TRIANGLES, GLsizei(indexes.size()), GL_UNSIGNED_INT, 0, instances);
    vertexArray->idle();
}

void Mesh::drawAdjacency(unsigned int instances)
{
    vertexArray->uploadIndexes(adjacencyIndexes);
    vertexArray->bind();
    glDrawElementsInstanced(GL_TRIANGLES_ADJACENCY, GLsizei(adjacencyIndexes.size()), GL_UNSIGNED_INT, 0, instances);
    vertexArray->idle();
}

void Mesh::verifyUVs()
{
    if (uvs.size() < vertexes.size()) {
        uvs.resize(vertexes.size(), vec2(0.f));
    }
}

void Mesh::initializeTriangleData()
{
    trianglesTangents.resize(vertexes.size(), fvec3(0.f, 0.f, 0.f));
    trianglesBitangents.resize(vertexes.size(), fvec3(0.f, 0.f, 0.f));
    trianglesPlaneEquations.reserve(triangles.size());
}

void Mesh::computeTrianglesTangents()
{
    std::vector<glm::vec3> tan1;
    std::vector<glm::vec3> tan2;

    tan1.reserve(vertexes.size() * 2);
    tan2.reserve(vertexes.size() * 2);

    for (auto &triangle : triangles) {
        unsigned int i1 = triangle[0];
        unsigned int i2 = triangle[1];
        unsigned int i3 = triangle[2];

        const vec4& v1 = vertexes[i1];
        const vec4& v2 = vertexes[i2];
        const vec4& v3 = vertexes[i3];

        const vec3 edge1 = vec3(v2 - v1);
        const vec3 edge2 = vec3(v3 - v1);

        const vec2& uv1 = uvs[i1];
        const vec2& uv2 = uvs[i2];
        const vec2& uv3 = uvs[i3];

        const vec2 deltaUV1 = uv2 - uv1;
        const vec2 deltaUV2 = uv3 - uv1;

        float f = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV2.x * deltaUV1.y);

        vec3 tangent = normalize(vec3(
            f * (deltaUV2.y * edge1.x - deltaUV1.y * edge2.x),
            f * (deltaUV2.y * edge1.y - deltaUV1.y * edge2.y),
            f * (deltaUV2.y * edge1.z - deltaUV1.y * edge2.z)
        ));

        vec3 bitangent = normalize(vec3(
            f * (-deltaUV2.x * edge1.x + deltaUV1.x * edge2.x),
            f * (-deltaUV2.x * edge1.y + deltaUV1.x * edge2.y),
            f * (-deltaUV2.x * edge1.z + deltaUV1.x * edge2.z)
        ));

        trianglesTangents[i1] = trianglesTangents[i2] = trianglesTangents[i3] = tangent;
        trianglesBitangents[i1] = trianglesBitangents[i2] = trianglesBitangents[i3] = bitangent;
    }
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
}
