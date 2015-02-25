#pragma once
#include <vector>
#include <climits>
#include <assert.h>
#include "System.hpp"
#include "Component.hpp"
#include "helpers/Mapper.hpp"

#define mask(n) ((1) << (n))

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
    bool hasComponent(Index entity);
    template <class T>
    T* addComponent(Index entity);
    template <class T>
    T* getComponent(Index entity);

private:
    void registerEntity(Index entity, Index index);
    void unregisterEntity(Index entity, Index index);
    void extendIndexCapacity();
    bool hasEntity(Index entity);

    template <class T>
    Index getComponentTypeIndex();

    Index entityCount = 0;

    Mapper mapper;
    std::vector<System> systems;
    std::vector<std::vector<Index>> entitiesComponentsIndex;
};

template <class T>
Index EntitiesManager::getComponentTypeIndex()
{
    Index index = Component<T>::typeIndex;
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

template <class T>
bool EntitiesManager::hasComponent(Index entity)
{
    if (hasEntity(entity)) {
        return entitiesComponentsIndex.at(entity).at(getComponentTypeIndex<T>()) != UINT_MAX;
    } else {
        throw std::invalid_argument("Entity index doesn't exist");
    }
}

// TODO return the first available component
template <class T>
T* EntitiesManager::addComponent(Index entity)
{
    if (hasEntity(entity)) {
        if (hasComponent<T>(entity)) {
            throw std::invalid_argument("Entity already has this component");
        } else {
            entitiesComponentsIndex.at(entity).at(getComponentTypeIndex<T>()) = unsigned(Component<T>::list.size());
            Component<T>::list.push_back(T());
            registerEntity(entity, getComponentTypeIndex<T>());
            return &Component<T>::list.back();
        }
    } else {
        throw std::invalid_argument("Entity index doesn't exist");
    }
}

template <class T>
T* EntitiesManager::getComponent(Index entity)
{
    if (hasEntity(entity)) {
        if (hasComponent<T>(entity)) {
            return &Component<T>::list.at(entitiesComponentsIndex.at(entity).at(getComponentTypeIndex<T>()));
        } else {
            throw std::invalid_argument("Entity already doesn't have this component");
        }
    } else {
        throw std::invalid_argument("Entity index doesn't exist");
    }
}

template <class T>
void EntitiesManager::delComponent(Index entity)
{
    if (hasEntity(entity)) {
        if (hasComponent<T>(entity)) {
            entitiesComponentsIndex.at(entity).at(getComponentTypeIndex<T>()) = UINT_MAX;
            unregisterEntity(entity, getComponentTypeIndex<T>());
        } else {
            throw std::invalid_argument("Entity already doesn't have this component");
        }
    } else {
        throw std::invalid_argument("Entity index doesn't exist");
    }
}
