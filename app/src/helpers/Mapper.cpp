#include "helpers/Mapper.hpp"

bool Mapper::has(unsigned int i)
{
    return (i < index.size() && index.at(i) != UINT_MAX);
}

void Mapper::add(unsigned int i)
{
    if (has(i)) return;
    if (index.size() <= i) index.resize(i + 1, UINT_MAX);
    index.at(i) = ++total - 1;
}

unsigned int Mapper::at(unsigned int i) const
{
    return index.at(i);
}
