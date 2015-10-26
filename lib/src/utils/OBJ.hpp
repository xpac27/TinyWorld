#pragma once
#include <GL/glew.h>
#include <vector>
#include <fstream>
#include <glm/fwd.hpp>

struct Material;

class OBJ
{

public:

    OBJ(std::vector<glm::uvec3> &_triangles, std::vector<glm::vec3> &_vertexes, std::vector<glm::vec2> &_uvs, std::vector<glm::vec3> &_normals, std::vector<unsigned int> &_indexes, std::vector<Material> &_materials)
        : triangles(_triangles)
        , vertexes(_vertexes)
        , uvs(_uvs)
        , normals(_normals)
        , indexes(_indexes)
        , materials(_materials)
    {}

    void load(const char *filename);
    void debug();

    static void debug(std::vector<glm::uvec3> &triangles, std::vector<glm::vec3> &vertexes, std::vector<glm::vec2> &uvs, std::vector<glm::vec3> &normals, std::vector<unsigned int> &indexes, std::vector<Material> &materials);

private:

    bool openFile(const char *filename, std::ifstream &fin);
    void parseLines(std::ifstream &fin);
    void parseVertex(std::ifstream &fin);
    void parseUVs(std::ifstream &fin);
    void parseNormal(std::ifstream &fin);
    void parseFace(std::ifstream &fin);
    void parseMTLLib(std::ifstream &fin);
    void skipNextChar(std::ifstream &fin);
    void skipLine(std::ifstream &fin);
    void addPoint(unsigned int values[3]);
    void addTriangle(unsigned int values[3]);

    std::vector<glm::uvec3> &triangles;
    std::vector<glm::vec3> &vertexes;
    std::vector<glm::vec2> &uvs;
    std::vector<glm::vec3> &normals;
    std::vector<unsigned int> &indexes;
    std::vector<Material> &materials;

    std::vector<glm::vec3> normalList;
    std::vector<glm::vec2> uvList;

    const char * MTLLIB = "mtllib";
    const char * VT = "vt";
    const char * VN = "vn";
    const char * V = "v";
    const char * F = "f";
};
