#include "utils/OBJLoader.hpp"
#include "graphic/Vertex.hpp"
#include "graphic/Normal.hpp"
#include "helpers/Debug.hpp"
#include <assert.h>

using namespace std;

void OBJLoader::loadOBJ(vector<Vertex> &vertexes, vector<Normal> &normals, vector<unsigned int> &indexes, const char *filename)
{
    ifstream fin(filename);
    if (!fin.good()) {
        Debug::printl("ERROR - could not open file:", filename);
    }

    vector<Normal> normalList;

    char b[1];
    bool ignoring = false;

    while (!fin.eof()) {
        if (ignoring) {
            fin.read(b, 1);
            if (b[0] == '\n') ignoring = false;
        } else {
            switch (identifyLigne(fin)) {
                case 1: parseVertex(vertexes, fin); break;
                case 2: /* parseTextures */ break;
                case 3: parseNormal(normalList, fin); break;
                case 4: parseFace(indexes, normals, normalList, fin); break;
                case 5: parseMTLLib(fin); break;
            }
            ignoring = true;
        }
    }

    assert(vertexes.size() == normals.size());
    assert(vertexes.size() <= indexes.size());
}

void OBJLoader::parseMTLLib(std::ifstream &fin)
{
    char m[80] {' '};
    fin >> m;
    Debug::printl(m);
}

unsigned int OBJLoader::identifyLigne(std::ifstream &fin)
{
    char k[10] {' '};
    fin >> k;
    char mtllib[] = "mtllib"; if (strncmp(k, mtllib, 6) == 0) return 5;
    char vt[] = "vt"; if (strncmp(k, vt, 2) == 0) return 2;
    char vn[] = "vn"; if (strncmp(k, vn, 2) == 0) return 3;
    char v[] = "v"; if (strncmp(k, v, 1) == 0) return 1;
    char f[] = "f"; if (strncmp(k, f, 1) == 0) return 4;
    return 0;
}

void OBJLoader::parseVertex(vector<Vertex> &vertexes, ifstream &fin)
{
    GLfloat f1, f2, f3;
    fin >> f1 >> f2 >> f3;
    vertexes.push_back(Vertex(f1, f2, f3));
}

void OBJLoader::parseNormal(vector<Normal> &normals, ifstream &fin)
{
    GLfloat f1, f2, f3;
    fin >> f1 >> f2 >> f3;
    normals.push_back(Normal(f1, f2, f3));
}

void OBJLoader::parseFace(std::vector<unsigned int> &indexes, std::vector<Normal> &normals, std::vector<Normal> &normalList, std::ifstream &fin)
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
                    // Textures coord...
                    fin.read(b, 1);
                    if (b[0] == ' ') break;
                } else if (j == 2) {
                    if (normals.size() < u[0]) normals.resize(u[0], Normal(0.f, 0.f, 0.f));
                    normals[u[0]-1] = normalList[u[2]-1];
                }
            } else {
                fin.clear();
                fin.ignore();
            }
        }
    }
}

void OBJLoader::debug(vector<Vertex> &vertexes, vector<Normal> &normals, vector<unsigned int> &indexes)
{
    for (auto v : vertexes) {
        Debug::printl("v", v.x, v.y, v.z);
    }
    for (auto n : normals) {
        Debug::printl("vn", n.x, n.y, n.z);
    }
    for (unsigned int i = 0; i < indexes.size(); i += 3) {
        Debug::printl("f", indexes[i+0], indexes[i+1], indexes[i+2]);
    }
}
