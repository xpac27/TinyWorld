#pragma once
#include <vector>
#include <fstream>

struct Material;

class MTLParser
{

public:

    void load(std::vector<Material> &materials, const char *filename);
    void debug(std::vector<Material> &materials);

private:

    bool openFile(const char *filename, std::ifstream &fin);
    void parseLines(std::vector<Material> &materials, std::ifstream &fin);
    unsigned int identifyLigne(std::ifstream &fin);
    void parseNewmtl(std::vector<Material> &materials, std::ifstream &fin);
    void parseMapBump(Material &material, std::ifstream &fin);
    void parseMapKd(Material &material, std::ifstream &fin);
    void parseMapKs(Material &material, std::ifstream &fin);
    void parseNs(Material &material, std::ifstream &fin);
    void parseKa(Material &material, std::ifstream &fin);
    void parseKd(Material &material, std::ifstream &fin);
    void parseKs(Material &material, std::ifstream &fin);
    void parseD(Material &material, std::ifstream &fin);

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
