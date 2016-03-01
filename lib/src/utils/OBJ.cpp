#include "OBJ.hpp"
#include "log.hpp"
#include <glm/glm.hpp>
#include <cstring>
#include <assert.h>

using namespace std;
using namespace glm;

OBJ::OBJ(std::vector<glm::uvec3> &_triangles, std::vector<glm::vec4> &_vertexes, std::vector<glm::vec2> &_uvs, std::vector<glm::vec3> &_normals, std::vector<unsigned int> &_indexes)
    : triangles(_triangles)
    , vertexes(_vertexes)
    , uvs(_uvs)
    , normals(_normals)
    , indexes(_indexes)
{}

void OBJ::load(const char *filename)
{
    ifstream fin;

    if (openFile(filename, fin)) {
        parseLines(fin);
    } else {
        error("OBJ not found:", filename);
    }

    triangles.shrink_to_fit();
    vertexes.shrink_to_fit();
    uvs.shrink_to_fit();
    normals.shrink_to_fit();
    indexes.shrink_to_fit();

    assert(vertexes.size() == uvs.size());
    assert(vertexes.size() == normals.size());
    assert(vertexes.size() <= indexes.size());

    success("OBJ loaded:", vertexes.size(), "vertexes,", triangles.size(), "triangles,", indexes.size(), "indexes,", filename);
}

bool OBJ::openFile(const char *filename, ifstream &fin)
{
    fin.open(filename);
    return fin.good();
}

void OBJ::parseLines(ifstream &fin)
{
    // TODO add asserts to notify of unsuported file format
    while (!fin.eof()) {
        char k[7] {' '};
        fin >> k;
        if (strncmp(k, VT, 3) == 0) {
            parseUVs(fin);
        } else if (strncmp(k, VN, 3) == 0) {
            parseNormal(fin);
        } else if (strncmp(k, V, 2) == 0) {
            parseVertex(fin);
        } else if (strncmp(k, F, 2) == 0) {
            parseFace(fin);
        } else {
            skipLine(fin);
        }
    }
}

void OBJ::skipLine(ifstream &fin)
{
    char b[1] = {' '};
    while (!fin.eof() && b[0] != '\n') {
        fin.read(b, 1);
    }
}

void OBJ::parseVertex(ifstream &fin)
{
    GLfloat f1, f2, f3;
    fin >> f1 >> f2 >> f3;
    vertexes.push_back(vec4(f1, f2, f3, 1.0f));
}

void OBJ::parseUVs(ifstream &fin)
{
    GLfloat f1, f2;
    fin >> f1 >> f2;
    uvList.push_back(vec2(f1, f2));
}

void OBJ::parseNormal(ifstream &fin)
{
    GLfloat f1, f2, f3;
    fin >> f1 >> f2 >> f3;
    normalList.push_back(vec3(f1, f2, f3));
}

void OBJ::parseFace(ifstream &fin)
{
    unsigned int values[3] {0};
    unsigned int faceIndexes[3] {0};
    for (unsigned int point = 0; point < 3; point ++) {
        for (unsigned int type = 0; type < 3; type ++) {
            fin >> values[type];
            skipNextChar(fin);
        }
        faceIndexes[point] = values[0] - 1;
        addPoint(values);
    }
    addTriangle(faceIndexes);
}

void OBJ::addPoint(unsigned int values[3])
{
    indexes.push_back(values[0] - 1);

    uvs.resize(vertexes.size());
    uvs[values[0] - 1] = uvList[values[1] - 1];

    normals.resize(vertexes.size());
    normals[values[0] - 1] = normalList[values[2] - 1];
}

void OBJ::addTriangle(unsigned int values[3])
{
    triangles.push_back(uvec3(values[0], values[1], values[2]));
}

void OBJ::skipNextChar(std::ifstream &fin)
{
    fin.clear();
    fin.ignore();
}

void OBJ::debug()
{
    OBJ::debug(triangles, vertexes, uvs, normals, indexes);
}

void OBJ::debug(std::vector<glm::uvec3> &triangles, std::vector<glm::vec4> &vertexes, std::vector<glm::vec2> &uvs, std::vector<glm::vec3> &normals, std::vector<unsigned int> &indexes)
{
    nl();
    info("printing mesh details");

    nl();
    info("  vertexes:");
    unsigned int index = 0;
    for (auto v : vertexes) {
        printl("    ", ++index, "=", v.x, v.y, v.z);
    }

    nl();
    info("  normals:");
    index = 0;
    for (auto n : normals) {
        printl("    ", ++index, "=", n.x, n.y, n.z);
    }

    nl();
    info("  uvs:");
    index = 0;
    for (auto u : uvs) {
        printl("    ", ++index, "=", u.x, u.y);
    }

    nl();
    info("  triangles:");
    for (auto t : triangles) {
        printl("    ", t.x + 1, t.y + 1, t.z + 1);
    }

    nl();
    info("    Totals indexes:", indexes.size());
}
