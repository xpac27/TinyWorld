#include "utils/OBJParser.hpp"
#include "utils/MTLParser.hpp"
#include "helpers/Debug.hpp"
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <cstring>
#include <assert.h>

using namespace std;
using namespace glm;

void OBJParser::load(const char *filename)
{
    ifstream fin;
    if (openFile(filename, fin)) {
        parseLines(fin);
    }
    assert(vertexes.size() == normals.size());
    assert(vertexes.size() <= indexes.size());
}

bool OBJParser::openFile(const char *filename, std::ifstream &fin)
{
    string filepath = "app/res/";
    filepath += filename;
    fin.open(filepath);
    if (!fin.good()) Debug::printl("ERROR - could not open file:", filepath);
    return fin.good();
}

void OBJParser::parseLines(std::ifstream &fin)
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

void OBJParser::parseVertex(ifstream &fin)
{
    GLfloat f1, f2, f3;
    fin >> f1 >> f2 >> f3;
    vertexes.push_back(vec3(f1, f2, f3));
}

void OBJParser::parseUVs(std::ifstream &fin)
{
    GLfloat f1, f2;
    fin >> f1 >> f2;
    uvList.push_back(vec2(f1, f2));
}

void OBJParser::parseNormal(ifstream &fin)
{
    GLfloat f1, f2, f3;
    fin >> f1 >> f2 >> f3;
    normalList.push_back(vec3(f1, f2, f3));
}

void OBJParser::parseFace(std::ifstream &fin)
{
    char b[1] {' '};
    unsigned int u[3] {0};
    for (unsigned int i = 0; i < 3; i ++) {
        for (unsigned int j = 0; j < 3; j ++) {
            fin >> u[j];
            if ((fin.rdstate() & std::ifstream::failbit) == 0) {
                if (j == 0) {
                    indexes.push_back(u[0]-1);
                    fin.read(b, 1);
                    if (b[0] == ' ') break;
                } else if (j == 1) {
                    if (uvs.size() < u[0]) {
                        uvs.resize(u[0], vec2());
                    }
                    uvs[u[0]-1] = uvList[u[1]-1];
                    fin.read(b, 1);
                    if (b[0] == ' ') break;
                } else if (j == 2) {
                    if (normals.size() < u[0]) {
                        normals.resize(u[0], vec3());
                    }
                    normals[u[0]-1] = normalList[u[2]-1];
                }
            } else {
                fin.clear();
                fin.ignore();
            }
        }
    }
}

void OBJParser::parseMTLLib(std::ifstream &fin)
{
    char c[80] {' '};
    fin >> c;
    MTLParser(materials).load(c);
}

void OBJParser::debug()
{
    Debug::printl("\n---- OBJ");
    for (auto v : vertexes) {
        Debug::printl("  v", v.x, v.y, v.z);
    }
    for (auto n : normals) {
        Debug::printl("  vn", n.x, n.y, n.z);
    }
    for (unsigned int i = 0; i < indexes.size(); i += 3) {
        Debug::printl("  f", indexes[i+0], indexes[i+1], indexes[i+2]);
    }
}
