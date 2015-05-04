#include "utils/MTLParser.hpp"
#include "graphic/Material.hpp"
#include "helpers/Debug.hpp"
#include <cstring>

using namespace std;

void MTLParser::load(std::vector<Material> &materials, const char *filename)
{
    ifstream fin;
    if (openFile(filename, fin)) {
        parseLines(materials, fin);
    }
}

bool MTLParser::openFile(const char *filename, std::ifstream &fin)
{
    string filepath = "app/res/";
    filepath += filename;
    fin.open(filepath);
    if (!fin.good()) Debug::printl("ERROR - could not open file:", filepath);
    return fin.good();
}

void MTLParser::parseLines(std::vector<Material> &materials, std::ifstream &fin)
{
    char b[1];
    bool ignoring = false;
    while (!fin.eof()) {
        if (ignoring) {
            fin.read(b, 1);
            if (b[0] == '\n') ignoring = false;
        } else {
            switch (identifyLigne(fin)) {
                case 1: parseMapBump(materials.back(), fin); break;
                case 2: parseMapKd(materials.back(), fin); break;
                case 3: parseMapKs(materials.back(), fin); break;
                case 4: parseNewmtl(materials, fin); break;
                case 5: parseNs(materials.back(), fin); break;
                case 6: parseKa(materials.back(), fin); break;
                case 7: parseKd(materials.back(), fin); break;
                case 8: parseKs(materials.back(), fin); break;
                case 9: parseD(materials.back(), fin); break;
            }
            ignoring = true;
        }
    }
}

unsigned int MTLParser::identifyLigne(std::ifstream &fin)
{
    char k[9] {' '};
    fin >> k;
    if (strncmp(k, MAP_BUMP, 9) == 0) return 1;
    if (strncmp(k, MAP_KD, 6) == 0) return 2;
    if (strncmp(k, MAP_KS, 6) == 0) return 3;
    if (strncmp(k, NEWMTL, 7) == 0) return 4;
    if (strncmp(k, NS, 3) == 0) return 5;
    if (strncmp(k, KA, 3) == 0) return 6;
    if (strncmp(k, KD, 3) == 0) return 7;
    if (strncmp(k, KS, 3) == 0) return 8;
    if (strncmp(k, D, 2) == 0) return 9;
    return 0;
}

void MTLParser::parseNewmtl(std::vector<Material> &materials, std::ifstream &fin)
{
    char c[80] {' '};
    fin >> c;
    materials.push_back(Material(c));
}

void MTLParser::parseMapBump(Material &material, std::ifstream &fin)
{
    char c[80] {' '};
    fin >> c;
    material.map_Bump = c;
}

void MTLParser::parseMapKd(Material &material, std::ifstream &fin)
{
    char c[80] {' '};
    fin >> c;
    material.map_Kd = c;
}

void MTLParser::parseMapKs(Material &material, std::ifstream &fin)
{
    char c[80] {' '};
    fin >> c;
    material.map_Ks = c;
}

void MTLParser::parseNs(Material &material, std::ifstream &fin)
{
    GLfloat f1;
    fin >> f1;
    material.Ns = f1;
}

void MTLParser::parseKa(Material &material, std::ifstream &fin)
{
    GLfloat f1, f2, f3;
    fin >> f1 >> f2 >> f3;
    material.Ka[0] = f1;
    material.Ka[1] = f2;
    material.Ka[2] = f3;
}

void MTLParser::parseKd(Material &material, std::ifstream &fin)
{
    GLfloat f1, f2, f3;
    fin >> f1 >> f2 >> f3;
    material.Kd[0] = f1;
    material.Kd[1] = f2;
    material.Kd[2] = f3;
}

void MTLParser::parseKs(Material &material, std::ifstream &fin)
{
    GLfloat f1, f2, f3;
    fin >> f1 >> f2 >> f3;
    material.Ks[0] = f1;
    material.Ks[1] = f2;
    material.Ks[2] = f3;
}

void MTLParser::parseD(Material &material, std::ifstream &fin)
{
    GLfloat f1;
    fin >> f1;
    material.d = f1;
}

void MTLParser::debug(std::vector<Material> &materials)
{
    for (auto m : materials) {
        Debug::printl("\n---- MTL");
        Debug::printl("  newmtl", m.name);
        Debug::printl("  Ns", m.Ns);
        Debug::printl("  Ka", m.Ka[0], m.Ka[1], m.Ka[2]);
        Debug::printl("  Kd", m.Kd[0], m.Kd[1], m.Kd[2]);
        Debug::printl("  Ks", m.Ks[0], m.Ks[1], m.Ks[2]);
        Debug::printl("  d", m.d);
        Debug::printl("  map_Kd", m.map_Kd);
        Debug::printl("  map_Ks", m.map_Ks);
        Debug::printl("  map_Bump", m.map_Bump);
    }
}

