#pragma once
#include <vector>

namespace ECS {
typedef unsigned long id;

template <typename T>
class ComponentManager
{
public:

    T* createComponent();
    T* getComponent(id entity);

    void addComponent(T *component, id entity);
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
void ComponentManager<T>::addComponent(T *component, id entity)
{
    // TODO check if this pointer is within components vector
    if (entitiesComponents.size() <= entity) {
        entitiesComponents.resize(entity + 1, nullptr);
    }
    entitiesComponents.at(entity) = component;
}

template <typename T>
void ComponentManager<T>::delComponent(id entity)
{
    // delete entitiesComponents.at(entity); // is that nessecary?
    // components.erase(entitiesComponents.at(entity)); // this wont work
    entitiesComponents.at(entity) = nullptr;
}

template <typename T>
bool ComponentManager<T>::hasComponent(id entity)
{
    return entity < entitiesComponents.size() && entitiesComponents.at(entity);
}

}
