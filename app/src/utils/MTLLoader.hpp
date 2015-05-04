#pragma once
#include <vector>
#include <fstream>

struct Material;

// TODO make non static
// TODO rename in MTLparser
class MTLLoader
{

public:

    static void load(std::vector<Material> &materials, const char *filename);
    static void debug(std::vector<Material> &materials);

private:

    static bool openFile(const char *filename, std::ifstream &fin);
    static void parseLines(std::vector<Material> &materials, std::ifstream &fin);
    static unsigned int identifyLigne(std::ifstream &fin);
    static void parseNewmtl(std::vector<Material> &materials, std::ifstream &fin);
    static void parseMapKd(Material &material, std::ifstream &fin);
    static void parseMapKs(Material &material, std::ifstream &fin);
};
