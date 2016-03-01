#include "Path.hpp"

using namespace std;

Path::Path(const string _location) : location(_location)
{
}

Path Path::get(const string path) const
{
    return Path(location + "/" + path);
}

const char* Path::data() const
{
    return location.data();
}

