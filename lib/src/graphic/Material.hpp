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
    std::string map_diffuse {"textures/default.png"};
    std::string map_metallic {"textures/default.png"};
    std::string map_rough {"textures/default.png"};
    std::string map_normal {""};

    Material(std::string _name)
        : name(_name)
    {}
};
