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
            }
            ignoring = true;
        }
    }

    assert(vertexes.size() == normals.size());
    assert(vertexes.size() <= indexes.size());
}

unsigned int OBJLoader::identifyLigne(std::ifstream &fin)
{
    char k[10] {' '}; fin >> k;
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
    unsigned int i1, i3;
    for (unsigned int i = 0; i < 3; i ++) {
        fin >> i1;
        fin.ignore();
        // no textures
        fin.ignore();
        fin >> i3;

        // Save index
        indexes.push_back(i1-1);

        // Save normal
        if (normals.size() < i1) normals.resize(i1, Normal(0.f, 0.f, 0.f));
        normals[i1-1] = normalList[i3-1];
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
