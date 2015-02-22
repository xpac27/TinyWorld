#pragma once
#include <vector>
#include <climits>

class Mapper
{
    public:

        bool add(unsigned int i);
        bool has(unsigned int i);
        unsigned int at(unsigned int i) const;

    private:

        unsigned int total = 0;
        std::vector<unsigned int> index;
};
