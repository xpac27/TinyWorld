#include "utils/OBJ.hpp"
#include "utils/MTL.hpp"
#include "graphic/Material.hpp"
#include "utils/Log.hpp"
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <cstring>
#include <assert.h>

using namespace std;
using namespace glm;
using namespace Log;

void OBJ::load(const char *filename)
{
    ifstream fin;
    if (openFile(filename, fin)) {
        parseLines(fin);
    }
    printl("obj loaded with ", vertexes.size(), "vertexes ", indexes.size(), "indexes");
    assert(vertexes.size() == uvs.size());
    assert(vertexes.size() == normals.size());
    assert(vertexes.size() <= indexes.size());
}

bool OBJ::openFile(const char *filename, ifstream &fin)
{
    string filepath = "app/res/";
    filepath += filename;
    fin.open(filepath);
    if (!fin.good()) printl("ERROR - could not open file:", filepath);
    return fin.good();
}

void OBJ::parseLines(ifstream &fin)
{
    // TODO add asserts to notify of unsuported file format
    while (!fin.eof()) {
        char k[7] {' '};
        fin >> k;
        if (strncmp(k, MTLLIB, 7) == 0) {
            parseMTLLib(fin);
        } else if (strncmp(k, VT, 3) == 0) {
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
    vertexes.push_back(vec3(f1, f2, f3));
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
    for (unsigned int point = 0; point < 3; point ++) {
        for (unsigned int type = 0; type < 3; type ++) {
            fin >> values[type];
            skipNextChar(fin);
        }
        addPoint(values);
    }
}

void OBJ::addPoint(unsigned int values[3])
{
    indexes.push_back(values[0] - 1);

    uvs.resize(vertexes.size());
    uvs[values[0] - 1] = uvList[values[1] - 1];

    normals.resize(vertexes.size());
    normals[values[0] - 1] = normalList[values[2] - 1];
}

void OBJ::skipNextChar(std::ifstream &fin)
{
    fin.clear();
    fin.ignore();
}

void OBJ::parseMTLLib(ifstream &fin)
{
    char c[80] {' '};
    fin >> c;
    MTL(materials).load(c);
}

void OBJ::debug()
{
    debug(vertexes, normals, indexes);
}

void OBJ::debug(vector<glm::vec3> &_vertexes, vector<glm::vec3> &_normals, vector<unsigned int> &_indexes)
{
    unsigned int index = 0;
    for (auto v : _vertexes) {
        printl(index++, "v", v.x, v.y, v.z);
    }
    print("\n");

    index = 0;
    for (auto n : _normals) {
        printl(index++, "vn", n.x, n.y, n.z);
    }
    print("\n");

    for (unsigned int i = 0; i < _indexes.size(); i += 3) {
        printl("-", _indexes[i+0], _indexes[i+1], _indexes[i+2]);
    }
    printl("\n---->>> ", _vertexes.size(), "v -", _normals.size(), "n -", _indexes.size(), "i");
}
