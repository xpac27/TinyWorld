#include "System.h"

void System::registerEntity(unsigned int entity)
{
    entities.push_back(entity);
}

void System::unregisterEntity(unsigned int entity)
{
    auto it = std::find(entities.begin(), entities.end(), entity);
    if (it != entities.end()) entities.erase(it);
}

bool System::useComponent(unsigned int mask) const
{
    return componentTypes & mask;
}

template<typename T>
bool System::useComponent() const
{
    return useComponent(mask(Component<T>::typeIndex));
}
