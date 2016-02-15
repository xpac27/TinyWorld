#include "../../inc/utils/PropertyList.hpp"

void PropertyList::put(PropertyName& key, PropertyValue& value)
{
    properties[key] = value;
}

const PropertyValue& PropertyList::get(PropertyName& key) const
{
    return properties.at(key);
}
