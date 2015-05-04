#pragma once
#include <GL/glew.h>
#include <string>

struct Material
{
    GLfloat d {0.f};
    GLfloat Ns {0.f};
    GLfloat Ka[3] {0.f, 0.f, 0.f};
    GLfloat Kd[3] {0.f, 0.f, 0.f};
    GLfloat Ks[3] {0.f, 0.f, 0.f};

    std::string name {""};
    std::string map_Kd {""};
    std::string map_Ks {""};
    std::string map_Bump {""};

    Material(std::string _name)
        : name(_name)
    {}
};
