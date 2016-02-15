#include "../../inc/utils/PropertyList.hpp"

void PropertyList::put(const PropertyName& key, const PropertyValueBase& value)
{
    properties.insert(std::pair<int, PropertyValueBase>(key, value));

    PropertyList list;
    list.put(PropertyName::ROOT_PATH(), PropertyValue<const char*>("rest"));
    const char* rootPath = list.get<const char*>(PropertyName::ROOT_PATH());
    (void)rootPath;

    // list[ROOT_PATH()] = Value<const char*>("rest");
    // const char* rootPath = list<const char*>[ROOT_PATH()];
}
