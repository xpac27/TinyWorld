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
    // for (glm::vec3 n : normals) {
    //     printl("  vn", n.x, n.y, n.z);
    // }
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
    char b[1];
    bool ignoring = false;
    while (!fin.eof()) {
        if (ignoring) {
            fin.read(b, 1);
            if (b[0] == '\n') ignoring = false;
        } else {
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
            }
            ignoring = true;
        }
    }
}

void OBJ::parseVertex(ifstream &fin)
{
    GLfloat f1, f2, f3;
    fin >> f1 >> f2 >> f3;
    vertexList.push_back(vec3(f1, f2, f3));
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
    char b[1] {' '};
    unsigned int u[3] {0};
    for (unsigned int i = 0; i < 3; i ++) {
        for (unsigned int j = 0; j < 3; j ++) {
            fin >> u[j];
            if ((fin.rdstate() & ifstream::failbit) == 0) {
                if (j == 0) {
                    vertexes.push_back(vertexList[u[0]-1]);
                    indexes.push_back(unsigned(vertexes.size()-1));
                    fin.read(b, 1);
                    if (b[0] == ' ') break;
                } else if (j == 1) {
                    uvs.push_back(uvList[u[1]-1]);
                    fin.read(b, 1);
                    if (b[0] == ' ') break;
                } else if (j == 2) {
                    normals.push_back(normalList[u[2]-1]);
                }
            } else {
                fin.clear();
                fin.ignore();
            }
        }
    }
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
    printl("\n---- OBJ");
    for (auto v : _vertexes) {
        printl("  v", v.x, v.y, v.z);
    }
    for (auto n : _normals) {
        printl("  vn", n.x, n.y, n.z);
    }
    for (unsigned int i = 0; i < _indexes.size(); i += 3) {
        printl("  f", _indexes[i+0], _indexes[i+1], _indexes[i+2]);
    }
}
