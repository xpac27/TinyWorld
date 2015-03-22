#pragma once
#include <vector>
#include <climits>

class Mapper
{
public:
    void add(unsigned int i);
    bool has(unsigned int i);

    unsigned int at(unsigned int i) const;
    unsigned int getTotal() const;

private:
    unsigned int total = 0;
    std::vector<unsigned int> index;
};
