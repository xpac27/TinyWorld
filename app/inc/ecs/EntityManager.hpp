#pragma once
#include <vector>
#include <climits>

#include "ecs/System.hpp"
#include "ecs/Component.hpp"

#include "helpers/Mapper.hpp"

#define mask(n) ((1) << (n))

namespace ECS
{

typedef unsigned int Index;

class EntitiesManager
{
public:
    Index addEntity();
    Index getEntityCount() const;

    void resetEntity(Index entity);
    void addSystem(System system);

    template <class T>
    void delComponent(Index entity);
    template <class T>
    T* addComponent(Index entity);
    template <class T>
    T* getComponent(Index entity);

private:
    void registerEntity(Index entity, Index index);
    void unregisterEntity(Index entity, Index index);
    void extendIndexCapacity();
    bool entityAvailable();
    bool hasEntity(Index entity);
    bool hasComponent(Index entity, Index index);
    bool hasNoComponent(Index entity, Index index);

    template <class T>
    Index getComponentTypeIndex();

    Index entityCount = 0;

    Mapper mapper;
    std::vector<System> systems;
    std::vector<std::vector<Index>> entitiesComponentsIndex;
};

}

// TODO find a better place for that (namespace?)
static unsigned int componentTypeCount = 0;

template <class T>
void ECS::EntitiesManager::delComponent(ECS::Index entity)
{
    if (hasComponent(entity, getComponentTypeIndex<T>())) {
        entitiesComponentsIndex.at(entity).at(getComponentTypeIndex<T>()) = UINT_MAX;
        unregisterEntity(entity, getComponentTypeIndex<T>());
    }
}

// TODO return the first available component
template <class T>
T* ECS::EntitiesManager::addComponent(ECS::Index entity)
{
    if (hasNoComponent(entity, getComponentTypeIndex<T>())) {
        entitiesComponentsIndex.at(entity).at(getComponentTypeIndex<T>()) = unsigned(Component<T>::list.size());
        Component<T>::list.push_back(T());
        registerEntity(entity, getComponentTypeIndex<T>());
    }
    return &Component<T>::list.back();
}

template <class T>
T* ECS::EntitiesManager::getComponent(ECS::Index entity)
{
    if (hasComponent(entity, getComponentTypeIndex<T>())) {
        return &Component<T>::list.at(entitiesComponentsIndex.at(entity).at(getComponentTypeIndex<T>()));
    } else {
        return nullptr;
    }
}

template <class T>
ECS::Index ECS::EntitiesManager::getComponentTypeIndex()
{
    ECS::Index index = Component<T>::typeIndex;
    if (mapper.has(index)) {
        return mapper.at(index);
    } else {
        if (Component<T>::typeIndex == UINT_MAX) {
            Component<T>::typeIndex = index = ++componentTypeCount - 1;
        }
        extendIndexCapacity();
        mapper.add(index);
    }
    return mapper.at(index);
}
