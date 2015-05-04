#pragma once
#include <string>

struct Material
{
    std::string name {""};
    std::string map_Kd {""};
    std::string map_Ks {""};

    Material(std::string _name)
        : name(_name)
    {}
};
