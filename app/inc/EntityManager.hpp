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

    template <class T>
    void addSystem();
    template <class T>
    void delComponent(Index entity);
    template <class T>
    bool hasComponent(Index entity);
    template <class T>
    T* addComponent(Index entity);
    template <class T>
    T* getComponent(Index entity);

private:
    template <class T>
    void registerEntity(Index entity);
    template <class T>
    void unregisterEntity(Index entity);
    template <class T>
    Index getComponentTypeIndex();

    Index entityCount = 0;

    Mapper mapper;

    std::vector<System> systems;
    std::vector<std::vector<Index>> entitiesComponentsIndex;
};

template <class T>
void EntitiesManager::addSystem()
{
    systems.push_back(T());
}

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
        for (auto& i : entitiesComponentsIndex) {
            i.push_back(UINT_MAX);
        }
        mapper.add(index);
    }
    return mapper.at(index);
}

template <class T>
bool EntitiesManager::hasComponent(Index entity)
{
    Index index = getComponentTypeIndex<T>();

    if (entitiesComponentsIndex.size() <= entity) {
        throw std::invalid_argument("Entity index doesn't exist");
    } else {
        return entitiesComponentsIndex.at(entity).at(index) != UINT_MAX;
    }
}

// TODO return the first available component
template <class T>
T* EntitiesManager::addComponent(Index entity)
{
    if (entitiesComponentsIndex.size() <= entity) {
        throw std::invalid_argument("Entity index doesn't exist");
    }

    Index index = getComponentTypeIndex<T>();

    if (entitiesComponentsIndex.at(entity).at(index) != UINT_MAX) {
        throw std::invalid_argument("Entity already has this component");
    } else {
        entitiesComponentsIndex.at(entity).at(index) = unsigned(Component<T>::list.size());
        Component<T>::list.push_back(T());
        registerEntity<T>(entity);
        return &Component<T>::list.back();
    }
}

template <class T>
T* EntitiesManager::getComponent(Index entity)
{
    Index index = getComponentTypeIndex<T>();

    if (entitiesComponentsIndex.size() <= entity) {
        throw std::invalid_argument("Entity index doesn't exist");
    } else if (entitiesComponentsIndex.at(entity).at(index) == UINT_MAX) {
        throw std::invalid_argument("Entity already doesn't have this component");
    } else {
        return &Component<T>::list.at(entitiesComponentsIndex.at(entity).at(index));
    }
}

template <class T>
void EntitiesManager::delComponent(Index entity)
{
    Index index = getComponentTypeIndex<T>();

    if (entitiesComponentsIndex.size() <= entity) {
        throw std::invalid_argument("Entity index doesn't exist");
    } else if (entitiesComponentsIndex.at(entity).at(index) == UINT_MAX) {
        throw std::invalid_argument("Entity doesn't have this component");
    } else {
        entitiesComponentsIndex.at(entity).at(index) = UINT_MAX;
        unregisterEntity<T>(entity);
    }
}

template <class T>
void EntitiesManager::registerEntity(Index entity)
{
    Index index = getComponentTypeIndex<T>();
    for (auto s : systems) {
        if (s.useComponent(index)) {
            s.registerEntity(entity);
        }
    }
}

template <class T>
void EntitiesManager::unregisterEntity(Index entity)
{
    Index index = getComponentTypeIndex<T>();
    for (auto s : systems) {
        if (s.useComponent(index)) {
            s.unregisterEntity(entity);
        }
    }
}

// TODO return the first available entity
Index EntitiesManager::addEntity()
{
    if (entityCount >= UINT_MAX) {
        throw std::out_of_range("You've reach the maximum number of entities!");
    } else {
        entitiesComponentsIndex.push_back(std::vector<Index>(componentTypeCount));
        std::fill(entitiesComponentsIndex.back().begin(), entitiesComponentsIndex.back().end(), UINT_MAX);
        return ++entityCount - 1;
    }
}

Index EntitiesManager::getEntityCount() const
{
    return entityCount;
}

void EntitiesManager::resetEntity(Index entity)
{
    if (entitiesComponentsIndex.size() <= entity) {
        throw std::invalid_argument("Entity index doesn't exist");
    } else {
        std::fill(entitiesComponentsIndex.at(entity).begin(), entitiesComponentsIndex.at(entity).end(), UINT_MAX);
    }
}
