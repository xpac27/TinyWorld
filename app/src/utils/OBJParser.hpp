#pragma once
#include <GL/glew.h>
#include <vector>
#include <fstream>
#include <glm/fwd.hpp>

struct Material;

class OBJParser
{

public:

    void load(std::vector<glm::vec3> &vertexes, std::vector<glm::vec3> &normals, std::vector<unsigned int> &indexes, const char *filename);
    void debug(std::vector<glm::vec3> &vertexes, std::vector<glm::vec3> &normals, std::vector<unsigned int> &indexes);

private:

    bool openFile(const char *filename, std::ifstream &fin);
    void parseLines(std::vector<glm::vec3> &vertexes, std::vector<glm::vec3> &normals, std::vector<unsigned int> &indexes, std::ifstream &fin);
    unsigned int identifyLigne(std::ifstream &fin);
    void parseVertex(std::vector<glm::vec3> &vertexes, std::ifstream &fin);
    void parseNormal(std::vector<glm::vec3> &normals, std::ifstream &fin);
    void parseFace(std::vector<unsigned int> &indexes, std::vector<glm::vec3> &normals, std::vector<glm::vec3> &normalList, std::ifstream &fin);
    void parseMTLLib(std::vector<Material> materials, std::ifstream &fin);

    const char * MTLLIB = "mtllib";
    const char * VT = "vt";
    const char * VN = "vn";
    const char * V = "v";
    const char * F = "f";
};
