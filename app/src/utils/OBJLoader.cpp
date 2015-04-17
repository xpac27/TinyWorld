#include "utils/OBJLoader.hpp"
#include "helpers/Debug.hpp"

using namespace std;

void OBJLoader::loadOBJ(vector<Vertex> &vertexes, vector<Normal> &normals, vector<GLubyte> &indexes, const char *filename)
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

void OBJLoader::parseFace(std::vector<Vertex> &vertexes, std::vector<Normal> &normals, std::vector<GLubyte> &indexes, std::ifstream &fin)
{
    unsigned int f;
    for (unsigned int v = 0; v < 3; v ++) {
        for (unsigned int i = 0; i < 3; i ++) {
            fin.ignore();
            fin >> f;
            f --;
            if ((fin.rdstate() & std::ifstream::failbit) != 0) {
                fin.clear();
            } else if (i == 0) {
                indexes.push_back(GLubyte(f));
            } else if (i == 1) {
                // Textures coords...
            } else if (i == 2) {
                vertexes[indexes.back()].nor[0] = GLfloat(normals[f].x);
                vertexes[indexes.back()].nor[1] = GLfloat(normals[f].y);
                vertexes[indexes.back()].nor[2] = GLfloat(normals[f].z);
            }
        }
    }
}
