#include "helpers/Mapper.hpp"

bool Mapper::has(unsigned int i)
{
    return (i < index.size() && index.at(i) != UINT_MAX);
}

bool Mapper::add(unsigned int i)
{
    if (has(i)) return false;
    if (index.size() <= i) index.resize(i + 1, UINT_MAX);
    index.at(i) = ++total - 1;
    return true;
}

unsigned int Mapper::at(unsigned int i) const
{
    return index.at(i);
}
