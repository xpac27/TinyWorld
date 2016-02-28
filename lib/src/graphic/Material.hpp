#pragma once
#include <OpenGL.hpp>
#include <string>

struct Material
{
    GLfloat d {0.f};
    GLfloat Ns {0.f};
    GLfloat Ka[3] {0.f, 0.f, 0.f};
    GLfloat Kd[3] {0.f, 0.f, 0.f};
    GLfloat Ks[3] {0.f, 0.f, 0.f};

    std::string name {""};
    std::string map_diffuse {"textures/default.png"};
    std::string map_metallic {};
    std::string map_rough {};
    std::string map_normal {""};

    Material(std::string _name)
        : name(_name)
    {}
};
