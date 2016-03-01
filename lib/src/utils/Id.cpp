#include "Id.hpp"
#include <iostream>

std::map<std::string, unsigned int> Id::names;

Id::Id(std::string name) : position(0)
{
    try {
        position = names.at(name);
    } catch(const std::exception&) {
        position = static_cast<unsigned int>(names.size());
        names[name] = position;
    }
}

Id::operator const unsigned int() const
{
    return position;
}
