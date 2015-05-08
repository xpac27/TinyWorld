#pragma once
#include <vector>
#include <fstream>

struct Material;

// TODO rename to MTL
class MTLParser
{

public:

    MTLParser(std::vector<Material> &_materials)
        : materials(_materials)
    {}

    void load(const char *filename);
    void debug();

private:

    bool openFile(const char *filename, std::ifstream &fin);
    void parseLines(std::ifstream &fin);
    void parseNewmtl(std::ifstream &fin);
    void parseMapBump(std::ifstream &fin);
    void parseMapKd(std::ifstream &fin);
    void parseMapKs(std::ifstream &fin);
    void parseNs(std::ifstream &fin);
    void parseKa(std::ifstream &fin);
    void parseKd(std::ifstream &fin);
    void parseKs(std::ifstream &fin);
    void parseD(std::ifstream &fin);

    std::vector<Material> &materials;

    const char * MAP_BUMP = "map_Bump";
    const char * MAP_KD = "map_Kd";
    const char * MAP_KS = "map_Ks";
    const char * NEWMTL = "newmtl";
    const char * NS = "Ns";
    const char * KA = "Ka";
    const char * KD = "Kd";
    const char * KS = "Ks";
    const char * D = "d";
};
