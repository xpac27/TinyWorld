#include "../../inc/utils/Path.hpp"

using namespace std;

Path::Path(const string _location) : location(_location)
{
}

Path Path::get(const string path) const
{
    return Path(location + "/" + path);
}

string Path::get() const
{
    return location;
}

