#include "utils/MTL.hpp"
#include "graphic/Material.hpp"
#include "utils/Log.hpp"
#include <cstring>

using namespace std;
using namespace Log;

void MTL::load(const char *filename)
{
    ifstream fin;
    if (openFile(filename, fin)) {
        parseLines(fin);
    }
}

bool MTL::openFile(const char *filename, ifstream &fin)
{
    string filepath = "lib/res/materials/";
    filepath += filename;
    fin.open(filepath);
    if (!fin.good()) printl("ERROR - could not open file:", filepath);
    return fin.good();
}

void MTL::parseLines(ifstream &fin)
{
    char b[1];
    bool ignoring = false;
    while (!fin.eof()) {
        if (ignoring) {
            fin.read(b, 1);
            if (b[0] == '\n') ignoring = false;
        } else {
            char k[9] {' '};
            fin >> k;
            if (strncmp(k, MAP_BUMP, 9) == 0) {
                parseMapBump(fin);
            } else if (strncmp(k, MAP_KD, 6) == 0) {
                parseMapKd(fin);
            } else if (strncmp(k, MAP_KS, 6) == 0) {
                parseMapKs(fin);
            } else if (strncmp(k, NEWMTL, 7) == 0) {
                parseNewmtl(fin);
            } else if (strncmp(k, NS, 3) == 0) {
                parseNs(fin);
            } else if (strncmp(k, KA, 3) == 0) {
                parseKa(fin);
            } else if (strncmp(k, KD, 3) == 0) {
                parseKd(fin);
            } else if (strncmp(k, KS, 3) == 0) {
                parseKs(fin);
            } else if (strncmp(k, D, 2) == 0) {
                parseD(fin);
            }
            ignoring = true;
        }
    }
}

void MTL::parseNewmtl(ifstream &fin)
{
    char c[80] {' '};
    fin >> c;
    materials.push_back(Material(c));
}

void MTL::parseMapBump(ifstream &fin)
{
    char c[80] {' '};
    fin >> c;
    materials.back().map_Bump = c;
}

void MTL::parseMapKd(ifstream &fin)
{
    char c[80] {' '};
    fin >> c;
    materials.back().map_Kd = c;
}

void MTL::parseMapKs(ifstream &fin)
{
    char c[80] {' '};
    fin >> c;
    materials.back().map_Ks = c;
}

void MTL::parseNs(ifstream &fin)
{
    GLfloat f1;
    fin >> f1;
    materials.back().Ns = f1;
}

void MTL::parseKa(ifstream &fin)
{
    GLfloat f1, f2, f3;
    fin >> f1 >> f2 >> f3;
    materials.back().Ka[0] = f1;
    materials.back().Ka[1] = f2;
    materials.back().Ka[2] = f3;
}

void MTL::parseKd(ifstream &fin)
{
    GLfloat f1, f2, f3;
    fin >> f1 >> f2 >> f3;
    materials.back().Kd[0] = f1;
    materials.back().Kd[1] = f2;
    materials.back().Kd[2] = f3;
}

void MTL::parseKs(ifstream &fin)
{
    GLfloat f1, f2, f3;
    fin >> f1 >> f2 >> f3;
    materials.back().Ks[0] = f1;
    materials.back().Ks[1] = f2;
    materials.back().Ks[2] = f3;
}

void MTL::parseD(ifstream &fin)
{
    GLfloat f1;
    fin >> f1;
    materials.back().d = f1;
}

void MTL::debug()
{
    for (auto m : materials) {
        printl("\n---- MTL");
        printl("  newmtl", m.name);
        printl("  Ns", m.Ns);
        printl("  Ka", m.Ka[0], m.Ka[1], m.Ka[2]);
        printl("  Kd", m.Kd[0], m.Kd[1], m.Kd[2]);
        printl("  Ks", m.Ks[0], m.Ks[1], m.Ks[2]);
        printl("  d", m.d);
        printl("  map_Kd", m.map_Kd);
        printl("  map_Ks", m.map_Ks);
        printl("  map_Bump", m.map_Bump);
    }
}
