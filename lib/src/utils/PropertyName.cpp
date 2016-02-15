#include "../../inc/utils/PropertyName.hpp"

PropertyName::PropertyName(int _type) : type(_type)
{
}

PropertyName::operator const int() const
{
    return type;
}

// bool PropertyName::operator <(PropertyName const& b)
// {
//     return type < static_cast<int>(b);
// }
//
// bool PropertyName::operator >(PropertyName const& b)
// {
//     return type > static_cast<int>(b);
// }
