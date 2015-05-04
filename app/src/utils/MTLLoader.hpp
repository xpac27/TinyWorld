#pragma once
#include <vector>
#include <fstream>

struct Material;

// TODO rename in MTLparser
class MTLLoader
{

public:

    void load(std::vector<Material> &materials, const char *filename);
    void debug(std::vector<Material> &materials);

private:

    bool openFile(const char *filename, std::ifstream &fin);
    void parseLines(std::vector<Material> &materials, std::ifstream &fin);
    unsigned int identifyLigne(std::ifstream &fin);
    void parseNewmtl(std::vector<Material> &materials, std::ifstream &fin);
    void parseMapKd(Material &material, std::ifstream &fin);
    void parseMapKs(Material &material, std::ifstream &fin);

    const char * NEWMTL = "newmtl";
    const char * MAP_KD = "map_Kd";
    const char * MAP_KS = "map_Ks";
};
