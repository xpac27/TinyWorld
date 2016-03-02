#pragma once
#include <map>
#include <string>

class Id
{

public:

    Id(std::string name);

    operator const unsigned int() const;

private:

    unsigned int position;

    static std::map<std::string, unsigned int> names;
};
