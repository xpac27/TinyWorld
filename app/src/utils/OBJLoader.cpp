#include "utils/OBJLoader.hpp"
#include "graphic/Vertex.hpp"
#include "graphic/Normal.hpp"
#include "helpers/Debug.hpp"

using namespace std;

void OBJLoader::loadOBJ(vector<Vertex> &vertexes, vector<Normal> &normals, vector<unsigned int> &indexes, const char *filename)
{
    char buffer[1];
    unsigned int state = 0; // 0 new line, 1 ignoring, 2 vertex, 3 face

    ifstream fin(filename);
    if (!fin.good()) {
        Debug::printl("ERROR - could not open file:", filename);
    }

    while (!fin.eof()) {

        fin.read(buffer, 1);

        if (state == 0) {
            if (buffer[0] == '\n') {
                state = 0;
            } else if (buffer[0] == '#') {
                state = 1;
            } else if (buffer[0] == 'v') {
                state = 2;
            } else if (buffer[0] == 'f') {
                state = 3;
            } else {
                state = 4;
            }
        } else {
            if (state == 1) {
                if (buffer[0] == '\n') {
                    state = 0;
                }
            } else {
                if (state == 2 && buffer[0] == ' ') {
                    parseVertex(vertexes, fin);
                } else if (state == 2 && buffer[0] == 't') {
                    // Textures coords...
                } else if (state == 2 && buffer[0] == 'n') {
                    parseNormal(normals, fin);
                } else if (state == 3 && buffer[0] == ' ') {
                    parseFace(vertexes, normals, indexes, fin);
                }
                state = 1;
            }
        }
    }
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

void OBJLoader::parseFace(std::vector<Vertex> &vertexes, std::vector<Normal> &normals, std::vector<unsigned int> &indexes, std::ifstream &fin)
{
    unsigned int i1, i3;
    for (unsigned int v = 0; v < 3; v ++) {
        fin >> i1;
        fin.ignore();
        // no textures
        fin.ignore();
        fin >> i3;
        indexes.push_back(i1-1);
        vertexes[i1-1].nor[0] = normals[i3-1].x;
        vertexes[i1-1].nor[1] = normals[i3-1].y;
        vertexes[i1-1].nor[2] = normals[i3-1].z;
    }
}

void OBJLoader::debug(vector<Vertex> &vertexes, vector<Normal> &normals, vector<unsigned int> &indexes)
{
    for (auto v : vertexes) {
        Debug::printl("v", v.pos[0], v.pos[1], v.pos[2]);
    }
    for (unsigned int i = 0; i < indexes.size(); i += 3) {
        Debug::printl("f", indexes[i+0], indexes[i+1], indexes[i+2]);
    }
}
