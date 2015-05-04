#pragma once
#include <GL/glew.h>
#include <vector>
#include <fstream>

struct Vertex;
struct Normal;
struct Material;

// TODO make non static
// TODO rename in OBJparser
class OBJLoader
{

public:

    static void load(std::vector<Vertex> &vertexes, std::vector<Normal> &normals, std::vector<unsigned int> &indexes, const char *filename);
    static void debug(std::vector<Vertex> &vertexes, std::vector<Normal> &normals, std::vector<unsigned int> &indexes);

private:

    static bool openFile(const char *filename, std::ifstream &fin);
    static void parseLines(std::vector<Vertex> &vertexes, std::vector<Normal> &normals, std::vector<unsigned int> &indexes, std::ifstream &fin);
    static unsigned int identifyLigne(std::ifstream &fin);
    static void parseVertex(std::vector<Vertex> &vertexes, std::ifstream &fin);
    static void parseNormal(std::vector<Normal> &normals, std::ifstream &fin);
    static void parseFace(std::vector<unsigned int> &indexes, std::vector<Normal> &normals, std::vector<Normal> &normalList, std::ifstream &fin);
    static void parseMTLLib(std::vector<Material> materials, std::ifstream &fin);
};
