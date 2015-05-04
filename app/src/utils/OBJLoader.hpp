#pragma once
#include <GL/glew.h>
#include <vector>
#include <fstream>

struct Vertex;
struct Normal;
struct Material;

// TODO rename in OBJparser
class OBJLoader
{

public:

    void load(std::vector<Vertex> &vertexes, std::vector<Normal> &normals, std::vector<unsigned int> &indexes, const char *filename);
    void debug(std::vector<Vertex> &vertexes, std::vector<Normal> &normals, std::vector<unsigned int> &indexes);

private:

    bool openFile(const char *filename, std::ifstream &fin);
    void parseLines(std::vector<Vertex> &vertexes, std::vector<Normal> &normals, std::vector<unsigned int> &indexes, std::ifstream &fin);
    unsigned int identifyLigne(std::ifstream &fin);
    void parseVertex(std::vector<Vertex> &vertexes, std::ifstream &fin);
    void parseNormal(std::vector<Normal> &normals, std::ifstream &fin);
    void parseFace(std::vector<unsigned int> &indexes, std::vector<Normal> &normals, std::vector<Normal> &normalList, std::ifstream &fin);
    void parseMTLLib(std::vector<Material> materials, std::ifstream &fin);

    const char * MTLLIB = "mtllib";
    const char * VT = "vt";
    const char * VN = "vn";
    const char * V = "v";
    const char * F = "f";
};
