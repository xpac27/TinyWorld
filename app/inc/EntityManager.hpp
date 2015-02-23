#pragma once
#include <vector>
#include <climits>
#include <assert.h>
#include "System.hpp"
#include "Component.hpp"
#include "helpers/Mapper.hpp"

#define mask(n) ((1) << (n))

typedef unsigned int Entity;

class EntitiesManager
{
public:
    Entity addEntity();
    Entity getEntityCount() const;

    void resetEntity(Entity entity);

    template <class T>
    void registerComponent();
    template <class T>
    void registerSystem();
    template <class T>
    void delComponent(Entity entity);
    template <class T>
    bool hasComponent(Entity entity) const;
    template <class T>
    T* addComponent(Entity entity);
    template <class T>
    T* getComponent(Entity entity) const;

private:
    template <class T>
    unsigned int getComponentTypeIndex() const;
    template <class T>
    void registerEntity(Entity entity) const;
    template <class T>
    void unregisterEntity(Entity entity) const;
    template <class T>
    void initComponentIndex() const;

    unsigned int entityCount = 0;

    Mapper mapper;

    std::vector<System> systems;
    std::vector<std::vector<unsigned int>> entitiesComponentsIndex;
};

template <class T>
void EntitiesManager::initComponentIndex() const
{
    if (Component<T>::typeIndex == UINT_MAX) {
        Component<T>::typeIndex = ++componentTypeCount - 1;
    }
}

// TODO repace unsigned int by typedef Index
template <class T>
unsigned int EntitiesManager::getComponentTypeIndex() const
{
    return mapper.at(Component<T>::typeIndex);
}

// TODO remove this function and use variadic template thus avoiding all tests to component being registered (and tests)
template <class T>
void EntitiesManager::registerComponent()
{
    initComponentIndex<T>();
    unsigned int index = Component<T>::typeIndex;

    if (mapper.has(index)) {
        throw std::invalid_argument("Component has already been registered");
    } else {
        mapper.add(index);
        for (auto& i : entitiesComponentsIndex) i.push_back(UINT_MAX);
    }
}

template <class T>
void EntitiesManager::registerSystem()
{
    systems.push_back(T());
}

template <class T>
bool EntitiesManager::hasComponent(Entity entity) const
{
    unsigned int index = Component<T>::typeIndex;

    if (entitiesComponentsIndex.size() <= entity) {
        throw std::invalid_argument("Entity index doesn't exist");
    } else if (entitiesComponentsIndex.at(entity).size() < index) {
        throw std::invalid_argument("Component has not been registered");
    } else {
        return entitiesComponentsIndex.at(entity).at(mapper.at(index)) != UINT_MAX;
    }
}

// TODO return the first available component
template <class T>
T* EntitiesManager::addComponent(Entity entity)
{
    unsigned int index = Component<T>::typeIndex;

    if (entitiesComponentsIndex.size() <= entity) {
        throw std::invalid_argument("Entity index doesn't exist");
    } else if (!mapper.has(index)) {
        throw std::invalid_argument("Component has not been registered");
    } else if (entitiesComponentsIndex.at(entity).at(mapper.at(index)) != UINT_MAX) {
        throw std::invalid_argument("Entity already has this component");
    } else {
        entitiesComponentsIndex.at(entity).at(mapper.at(index)) = unsigned(Component<T>::list.size());
        Component<T>::list.push_back(T());
        registerEntity<T>(entity);
        return &Component<T>::list.back();
    }
}

template <class T>
T* EntitiesManager::getComponent(Entity entity) const
{
    unsigned int index = Component<T>::typeIndex;

    if (entitiesComponentsIndex.size() <= entity) {
        throw std::invalid_argument("Entity index doesn't exist");
    } else if (entitiesComponentsIndex.at(entity).size() < index) {
        throw std::invalid_argument("Component has not been registered");
    } else if (entitiesComponentsIndex.at(entity).at(mapper.at(index)) == UINT_MAX) {
        throw std::invalid_argument("Entity already doesn't have this component");
    } else {
        return &Component<T>::list.at(entitiesComponentsIndex.at(entity).at(index));
    }
}

template <class T>
void EntitiesManager::delComponent(Entity entity)
{
    unsigned int index = Component<T>::typeIndex;

    if (entitiesComponentsIndex.size() <= entity) {
        throw std::invalid_argument("Entity index doesn't exist");
    } else if (entitiesComponentsIndex.at(entity).size() < index) {
        throw std::invalid_argument("Component has not been registered");
    } else if (entitiesComponentsIndex.at(entity).at(mapper.at(index)) == UINT_MAX) {
        throw std::invalid_argument("Entity doesn't have this component");
    } else {
        entitiesComponentsIndex.at(entity).at(mapper.at(index)) = UINT_MAX;
        unregisterEntity<T>(entity);
    }
}

template <class T>
void EntitiesManager::registerEntity(Entity entity) const
{
    unsigned int index = Component<T>::typeIndex;
    for (auto s : systems) {
        if (s.useComponent(mask(index))) {
            s.registerEntity(entity);
        }
    }
}

template <class T>
void EntitiesManager::unregisterEntity(Entity entity) const
{
    unsigned int index = Component<T>::typeIndex;
    for (auto s : systems) {
        if (s.useComponent(mask(index))) {
            s.unregisterEntity(entity);
        }
    }
}

// TODO return the first available entity
Entity EntitiesManager::addEntity()
{
    if (entityCount >= UINT_MAX) {
        throw std::out_of_range("You've reach the maximum number of entities!");
    } else {
        entitiesComponentsIndex.push_back(std::vector<unsigned int>(componentTypeCount));
        std::fill(entitiesComponentsIndex.back().begin(), entitiesComponentsIndex.back().end(), UINT_MAX);
        return ++entityCount - 1;
    }
}

unsigned int EntitiesManager::getEntityCount() const
{
    return entityCount;
}

void EntitiesManager::resetEntity(Entity entity)
{
    if (entitiesComponentsIndex.size() <= entity) {
        throw std::invalid_argument("Entity index doesn't exist");
    } else {
        std::fill(entitiesComponentsIndex.at(entity).begin(), entitiesComponentsIndex.at(entity).end(), UINT_MAX);
    }
}
