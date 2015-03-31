#pragma once
#include <vector>
#include <assert.h>
#include "ComponentManagerBase.hpp"
#include "helpers/Debug.hpp"
#include "Id.hpp"

namespace ECS {

template <typename T>
class ComponentManager : public ComponentManagerBase
{
public:

    T* getComponent(id entity);

    void addComponent(id entity);
    void delComponent(id entity);
    bool hasComponent(id entity);

private:

    std::vector<T> components;
    std::vector<int> entitiesComponents;
};

template <typename T>
T* ComponentManager<T>::getComponent(id entity)
{
    assert(entitiesComponents.size() > entity);
    return &components[unsigned(entitiesComponents[entity])];
}

template <typename T>
void ComponentManager<T>::addComponent(id entity)
{
    if (entitiesComponents.size() <= entity) {
        entitiesComponents.resize(entity + 1, -1);
    }
    if (entitiesComponents[entity] == -1) {
        // TODO find the first available component instead
        components.push_back(T());
        entitiesComponents[entity] = int(components.size()) - 1;
        fireEntityAddedSignal(entity);
    }
}

template <typename T>
void ComponentManager<T>::delComponent(id entity)
{
    assert(entitiesComponents.size() > entity);
    entitiesComponents[entity] = -1;
    fireEntityRemovedSignal(entity);
}

template <typename T>
bool ComponentManager<T>::hasComponent(id entity)
{
    return entity < entitiesComponents.size() && entitiesComponents[entity] != -1;
}
}
