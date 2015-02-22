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

        template<class T>
            void registerComponent();
        template<class T>
            void registerSystem();
        template<class T>
            void delComponent(Entity entity);
        template<class T>
            bool hasComponent(Entity entity) const;
        template<class T>
            T* addComponent(Entity entity);
        template<class T>
            T* getComponent(Entity entity) const;

    private:

        template<class T>
            unsigned int getComponentTypeIndex() const;

        unsigned int entityCount = 0;

        Mapper mapper;

        std::vector<System> systems;
        std::vector<std::vector<unsigned int>> entitiesComponentsIndex;
};

template<class T>
unsigned int EntitiesManager::getComponentTypeIndex() const
{
    return mapper.at(Component<T>::typeIndex);
}

template<class T>
void EntitiesManager::registerComponent()
{
    // TODO put in a method
    unsigned int index = Component<T>::typeIndex;
    if (index == UINT_MAX)
    {
        Component<T>::typeIndex = index = ++componentTypeCount - 1;
    }

    if (!mapper.add(index))
    {
        throw std::logic_error("Component has already been registered");
    }

    for (auto & i : entitiesComponentsIndex) i.push_back(UINT_MAX);
}

template<class T>
void EntitiesManager::registerSystem()
{
    systems.push_back(T());
}

template<class T>
bool EntitiesManager::hasComponent(Entity entity) const
{
    unsigned int index = Component<T>::typeIndex;

    if (entitiesComponentsIndex.size() < entity)
    {
        throw std::logic_error("Entity index doesn't exist");
    }
    if (entitiesComponentsIndex.at(entity).size() < index)
    {
        throw std::logic_error("Component has not been registered");
    }

    return entitiesComponentsIndex.at(entity).at(mapper.at(index)) != UINT_MAX;
}

// TODO return the first available component
template<class T>
T* EntitiesManager::addComponent(Entity entity)
{
    unsigned int index = Component<T>::typeIndex;

    if (entitiesComponentsIndex.size() < entity)
    {
        throw std::logic_error("Entity index doesn't exist");
    }
    if (!mapper.has(index))
    {
        throw std::logic_error("Component has not been registered");
    }
    if (entitiesComponentsIndex.at(entity).at(mapper.at(index)) != UINT_MAX)
    {
        throw std::logic_error("Entity already has this component");
    }

    entitiesComponentsIndex.at(entity).at(mapper.at(index)) = unsigned(Component<T>::list.size());
    Component<T>::list.push_back(T());
    // TODO put in a method
    for (auto s : systems)
    {
        if (s.useComponent(mask(index)))
        {
            s.registerEntity(entity);
        }
    }
    return &Component<T>::list.back();
}

// TODO throw instead of assert and TEST
template<class T>
T* EntitiesManager::getComponent(Entity entity) const
{
    unsigned int index = Component<T>::typeIndex;

    assert(entitiesComponentsIndex.size() > entity);
    assert(entitiesComponentsIndex.at(entity).size() > index);
    assert(Component<T>::list.size() > entitiesComponentsIndex.at(entity).at(index));

    return &Component<T>::list.at(entitiesComponentsIndex.at(entity).at(index));
}

// TODO throw instead of assert and TEST
template<class T>
void EntitiesManager::delComponent(Entity entity)
{
    unsigned int index = Component<T>::typeIndex;

    assert(entitiesComponentsIndex.size() > entity);
    assert(entitiesComponentsIndex.at(entity).size() > index);

    entitiesComponentsIndex.at(entity).at(mapper.at(index)) = UINT_MAX;
    // TODO put in a method
    for (auto s : systems)
    {
        if (s.useComponent(mask(index)))
        {
            s.unregisterEntity(entity);
        }
    }
}

// TODO return the first available entity
// TODO throw instead of assert and TEST
Entity EntitiesManager::addEntity()
{
    assert(entityCount < UINT_MAX);

    entitiesComponentsIndex.push_back(std::vector<unsigned int>(componentTypeCount));
    std::fill(entitiesComponentsIndex.back().begin(), entitiesComponentsIndex.back().end(), UINT_MAX);
    return ++entityCount - 1;
}

unsigned int EntitiesManager::getEntityCount() const
{
    return entityCount;
}

// TODO throw instead of assert and TEST
void EntitiesManager::resetEntity(Entity entity)
{
    assert(entitiesComponentsIndex.size() > entity);

    std::fill(entitiesComponentsIndex.at(entity).begin(), entitiesComponentsIndex.at(entity).end(), UINT_MAX);
}
