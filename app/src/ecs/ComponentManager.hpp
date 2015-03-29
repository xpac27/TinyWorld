#pragma once
#include <vector>
#include "Entity.hpp"
#include "ComponentManagerBase.hpp"

namespace ECS {

template <typename T>
class ComponentManager : public ComponentManagerBase
{
public:

    T* createComponent();
    T* getComponent(id entity);

    void addComponent(T* component, id entity);
    void delComponent(id entity);
    bool hasComponent(id entity);

private:

    std::vector<T> components {};
    std::vector<T*> entitiesComponents {};
};

template <typename T>
T* ComponentManager<T>::createComponent()
{
    components.push_back(T());
    return &components.back();
}

template <typename T>
T* ComponentManager<T>::getComponent(id entity)
{
    return entitiesComponents.at(entity);
}

template <typename T>
void ComponentManager<T>::addComponent(T* component, id entity)
{
    if (entitiesComponents.size() <= entity) {
        entitiesComponents.resize(entity + 1, nullptr);
    }
    entitiesComponents.at(entity) = component;
    fireEntityAddedSignal(entity);
}

template <typename T>
void ComponentManager<T>::delComponent(id entity)
{
    entitiesComponents.at(entity) = nullptr;
    components.erase(components.begin() + long(entity)); // NOTE could be optimized
    fireEntityRemovedSignal(entity);
}

template <typename T>
bool ComponentManager<T>::hasComponent(id entity)
{
    return entity < entitiesComponents.size() && entitiesComponents.at(entity);
}
}
