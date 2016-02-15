#pragma once
#include <map>
#include "PropertyName.hpp"
#include "PropertyValue.hpp"

class PropertyList
{

public:

    void put(PropertyName& key, PropertyValue& value);

    const PropertyValue& get(PropertyName& key) const;

private:

    std::map<PropertyName, PropertyValue> properties;
};
