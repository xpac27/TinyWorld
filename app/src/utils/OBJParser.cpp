#include "utils/OBJParser.hpp"
#include "utils/MTLParser.hpp"
#include "graphic/Vertex.hpp"
#include "graphic/Normal.hpp"
#include "graphic/Material.hpp"
#include "helpers/Debug.hpp"
#include <cstring>
#include <assert.h>

using namespace std;

void OBJParser::load(vector<Vertex> &vertexes, vector<Normal> &normals, vector<unsigned int> &indexes, const char *filename)
{
    ifstream fin;
    if (openFile(filename, fin)) {
        parseLines(vertexes, normals, indexes, fin);
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


void OBJParser::parseLines(std::vector<Vertex> &vertexes, std::vector<Normal> &normals, std::vector<unsigned int> &indexes, std::ifstream &fin)
{
    char b[1];
    bool ignoring = false;
    vector<Normal> normalList;
    vector<Material> materials;
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
                case 5: parseMTLLib(materials, fin); break;
            }
            ignoring = true;
        }
    }
}

unsigned int OBJParser::identifyLigne(std::ifstream &fin)
{
    char k[7] {' '};
    fin >> k;
    if (strncmp(k, MTLLIB, 7) == 0) return 5;
    if (strncmp(k, VT, 3) == 0) return 2;
    if (strncmp(k, VN, 3) == 0) return 3;
    if (strncmp(k, V, 2) == 0) return 1;
    if (strncmp(k, F, 2) == 0) return 4;
    return 0;
}

void OBJParser::parseVertex(vector<Vertex> &vertexes, ifstream &fin)
{
    GLfloat f1, f2, f3;
    fin >> f1 >> f2 >> f3;
    vertexes.push_back(Vertex(f1, f2, f3));
}

void OBJParser::parseNormal(vector<Normal> &normals, ifstream &fin)
{
    GLfloat f1, f2, f3;
    fin >> f1 >> f2 >> f3;
    normals.push_back(Normal(f1, f2, f3));
}

void OBJParser::parseFace(std::vector<unsigned int> &indexes, std::vector<Normal> &normals, std::vector<Normal> &normalList, std::ifstream &fin)
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

void OBJParser::parseMTLLib(vector<Material> materials, std::ifstream &fin)
{
    char c[80] {' '};
    fin >> c;
    MTLParser().load(materials, c);
    MTLParser().debug(materials);
}

void OBJParser::debug(vector<Vertex> &vertexes, vector<Normal> &normals, vector<unsigned int> &indexes)
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
