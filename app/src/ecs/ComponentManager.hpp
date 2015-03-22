#pragma once
#include <vector>

namespace ECS {
typedef size_t id;

template <typename T>
class ComponentManager
{
public:

    T& registerComponent(const T &component);
    T& getComponent(id entity);

    void addComponent(T &component, id entity);
    void delComponent(id entity);
    bool hasComponent(id entity);

private:

    std::vector<T> components {};
    std::vector<T*> entitiesComponents {};
};

template <typename T>
T& ComponentManager<T>::registerComponent(const T &component)
{
    components.push_back(component);
    return components.back();
}

template <typename T>
T& ComponentManager<T>::getComponent(id entity)
{
    return *entitiesComponents.at(entity);
}

template <typename T>
void ComponentManager<T>::addComponent(T &component, id entity)
{
    if (entitiesComponents.size() <= entity) {
        entitiesComponents.resize(entity + 1, nullptr);
    }
    entitiesComponents.at(entity) = &component;
}

template <typename T>
void ComponentManager<T>::delComponent(id entity)
{
    delete entitiesComponents.at(entity); // is that nessecary?
    components.erase(entitiesComponents.at(entity)); // this wont work
    entitiesComponents.at(entity) = nullptr;
}

template <typename T>
bool ComponentManager<T>::hasComponent(id entity)
{
    return entity < entitiesComponents.size() && entitiesComponents.at(entity);
}

}
