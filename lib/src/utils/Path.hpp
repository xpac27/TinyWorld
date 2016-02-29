#pragma once
#include <string>

class Path
{

public:

    Path() = delete;
    Path(const std::string location);
    Path get(const std::string path) const;

    const char* data() const;

private:

    std::string location;

};
