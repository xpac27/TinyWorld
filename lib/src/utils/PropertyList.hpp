#pragma once
#include <map>
#include "PropertyName.hpp"
#include "PropertyValue.hpp"

class PropertyList
{

public:

    void put(const PropertyName& key, const PropertyValueBase& value);

    template <typename T>
    const PropertyValue<T>& get(const PropertyName& key) const;

private:

    std::map<int, PropertyValueBase> properties;
};

template <typename T>
const PropertyValue<T>& PropertyList::get(const PropertyName& key) const
{
    return static_cast<T>(properties.at(key));
}
