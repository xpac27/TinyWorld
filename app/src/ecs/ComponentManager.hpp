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

    void createComponent(id entity);
    void reuseComponent(id entity);
    void resetComponent(id entity);
    void reserveComponentIndex(id entity);

    std::vector<T> components;
    std::vector<int> deletedComponentsIndex;
    std::vector<int> entitiesComponentsIndex;
};

template <typename T>
T* ComponentManager<T>::getComponent(id entity)
{
    assert(entitiesComponentsIndex.size() > entity && "ComponentManager: entity out of range");
    return &components[unsigned(entitiesComponentsIndex[entity])];
}

template <typename T>
void ComponentManager<T>::addComponent(id entity)
{
    if (hasComponent(entity)) {
        resetComponent(entity);
    } else {
        reserveComponentIndex(entity);
        deletedComponentsIndex.size() == 0 ? createComponent(entity) : reuseComponent(entity);
        fireEntityAddedSignal(entity);
    }
}

template <typename T>
void ComponentManager<T>::delComponent(id entity)
{
    assert(entitiesComponentsIndex.size() > entity && "ComponentManager: entity out of range");
    deletedComponentsIndex.push_back(entitiesComponentsIndex[entity]);
    entitiesComponentsIndex[entity] = -1;
    fireEntityRemovedSignal(entity);
}

template <typename T>
bool ComponentManager<T>::hasComponent(id entity)
{
    return entity < entitiesComponentsIndex.size() && entitiesComponentsIndex[entity] != -1;
}

template <typename T>
void ComponentManager<T>::createComponent(id entity)
{
    assert(entitiesComponentsIndex.size() > entity && "ComponentManager: entity out of range");
    entitiesComponentsIndex[entity] = int(components.size());
    components.push_back(T());
}

template <typename T>
void ComponentManager<T>::reuseComponent(id entity)
{
    assert(deletedComponentsIndex.size() > 0 && "ComponentManager: no reusable components");
    entitiesComponentsIndex[entity] = deletedComponentsIndex.back();
    deletedComponentsIndex.pop_back();
    resetComponent(entity);
}

template <typename T>
void ComponentManager<T>::resetComponent(id entity)
{
    components[unsigned(entitiesComponentsIndex[unsigned(entity)])] = T();
}

template <typename T>
void ComponentManager<T>::reserveComponentIndex(id entity)
{
    if (entitiesComponentsIndex.size() <= entity) {
        entitiesComponentsIndex.resize(entity + 1, -1);
    }
}
}
