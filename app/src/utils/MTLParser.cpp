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
                case 1: parseNewmtl(materials, fin); break;
                case 3: parseMapKd(materials.back(), fin); break;
                case 4: parseMapKs(materials.back(), fin); break;
            }
            ignoring = true;
        }
    }
}

unsigned int MTLParser::identifyLigne(std::ifstream &fin)
{
    char k[6] {' '};
    fin >> k;
    if (strncmp(k, NEWMTL, 6) == 0) return 1;
    if (strncmp(k, MAP_KD, 5) == 0) return 3;
    if (strncmp(k, MAP_KS, 5) == 0) return 4;
    return 0;
}

void MTLParser::parseNewmtl(std::vector<Material> &materials, std::ifstream &fin)
{
    char c[80] {' '};
    fin >> c;
    materials.push_back(Material(c));
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

void MTLParser::debug(std::vector<Material> &materials)
{
    for (auto m : materials) {
        Debug::printl("newmtl", m.name);
        Debug::printl("map_Kd", m.map_Kd);
        Debug::printl("map_Ks", m.map_Ks);
    }
}
