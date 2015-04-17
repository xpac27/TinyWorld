#pragma once
#include "graphic/Vertex.hpp"
#include "graphic/Normal.hpp"
#include <SFML/OpenGL.hpp>
#include <vector>
#include <fstream>

class OBJLoader
{

public:

    static void loadOBJ(std::vector<Vertex> &vertexes, std::vector<Normal> &normals, std::vector<GLubyte> &indexes, const char *filename);

private:

    static void parseVertex(std::vector<Vertex> &vertexes, std::ifstream &fin);
    static void parseNormal(std::vector<Normal> &normals, std::ifstream &fin);
    static void parseFace(std::vector<Vertex> &vertexes, std::vector<Normal> &normals, std::vector<GLubyte> &indexes, std::ifstream &fin);
};
